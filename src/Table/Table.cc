#include "Table.h"
#include "../TableCell/EmptyCell/EmptyCell.h"

void Table::deleteIfDeletable(CellPtr cellPtr) noexcept {
    if(cellPtr->isDeletable()) {
        delete cellPtr;
    }
}

Table::~Table() noexcept {
    tableRows.forEach([](const RowPtr rowPtr, size_t) noexcept {
        rowPtr->forEach([](CellPtr cellPtr, size_t) noexcept {
            deleteIfDeletable(cellPtr);
        });
        delete rowPtr;
    });
}

Table::TableIndex::TableIndex(size_t row, size_t col) noexcept
: rowIndex{row}, columnIndex{col} {}

size_t Table::TableIndex::getRow() const noexcept {
    return rowIndex;
}

size_t Table::TableIndex::getColumn() const noexcept {
    return columnIndex;
}

size_t Table::getRowsCount() const noexcept {
    if(!tableRows.isEmpty()) {
        bool containsNoneEmptyCell = false;
        tableRows.forEach([&containsNoneEmptyCell](const RowPtr rowPtr, size_t) noexcept {
            if(containsNoneEmptyCell) {
                return;
            }
            if(!rowPtr->isEmpty()) {
                containsNoneEmptyCell = true;
            }
        });
        if(containsNoneEmptyCell) {
            return tableRows.getLastElementIndex() + 1;
        }
    }
    return 0;
}

size_t Table::getColumnsCount() const noexcept {
    size_t columnsCount = 0;
    tableRows.forEach([&columnsCount](const RowPtr rowPtr, size_t) noexcept {
        if(!rowPtr->isEmpty()) {
            const size_t lastRowIndex = rowPtr->getLastElementIndex() + 1;
            if(lastRowIndex > columnsCount) {
                columnsCount = lastRowIndex;
            }
        }
    });
    return columnsCount;
}

bool Table::isEmptyCell(CellPtr cellPtr) noexcept {
    return cellPtr == EmptyCell::obtainPtr();
}

bool Table::clean(const RowPtr rowPtr, size_t index) noexcept {
    CellPtr cellPtr;
    try {
        cellPtr = rowPtr->getElement(index);
    } catch (Exception& error) {
        return false;
    }
    deleteIfDeletable(cellPtr);
    return true;
}

void Table::removeEmptyCells(const RowPtr rowPtr) noexcept {
    if(!rowPtr->isEmpty()) {
        size_t index = rowPtr->getLastElementIndex();
        while(isEmptyCell(rowPtr->getElement(index))) {
            rowPtr->removeElement(index);
            index = rowPtr->getLastElementIndex();
        }
    }
}

void Table::edit(const TableIndex& index, CellPtr cellPtr) {
    RowPtr rowPtr;
    const size_t row = index.getRow();
    const size_t column = index.getColumn();
    const bool isTableCellEmptyCell = isEmptyCell(cellPtr);
    try {
        rowPtr = tableRows[row];
    } catch(const Exception& error) {
        if(isTableCellEmptyCell) {
            return;
        }
        rowPtr = new Row;
        tableRows.setElement(rowPtr, row);
    }
    if(!isTableCellEmptyCell) {
        rowPtr->setElement(cellPtr, column);
        return;
    }
    if(clean(rowPtr, column)) {
        try {
            rowPtr->removeElement(column);
        } catch(const OperationNotPermitted& error) {
            rowPtr->setElement(cellPtr, column);
            return;
        }
        removeEmptyCells(rowPtr);
    }
}

const TableCell& Table::operator[](const TableIndex& index) const {
    RowPtr rowPtr;
    try {
        rowPtr = tableRows[index.getRow()];
    } catch(const Exception& error) {
        return EmptyCell::obtainRef();
    }
    CellPtr cellPtr;
    try {
        cellPtr = rowPtr->getElement(index.getColumn());
    } catch(const Exception& error) {
        return EmptyCell::obtainRef();
    }
    return *cellPtr;
}