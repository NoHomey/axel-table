#include "Table.h"
#include "../TableCell/EmptyCell/EmptyCell.h"

void Table::deleteIfDeletable(CellPtr cellPtr) noexcept {
    if(cellPtr->isDeletable()) {
        delete cellPtr;
    }
}

void Table::deleteCellsInRow(CellPtr cellPtr, size_t) noexcept {
    deleteIfDeletable(cellPtr);
}

void Table::deleteRow(const RowPtr rowPtr, size_t) noexcept {
    rowPtr->forEach(deleteCellsInRow);
    delete rowPtr;
}

Table::~Table() noexcept {
    tableRows.forEach(deleteRow);
}

Table::TableIndex::TableIndex(size_t row, size_t col) noexcept
: rowIndex{row}, columnIndex{col} {}

size_t Table::TableIndex::getRow() const noexcept {
    return rowIndex;
}

size_t Table::TableIndex::getColumn() const noexcept {
    return columnIndex;
}

Table::ColumnsCountFinder::ColumnsCountFinder() noexcept
: maxRowIndex{0} { }

void Table::ColumnsCountFinder::operator()(const RowPtr rowPtr, size_t) noexcept {
    const size_t lastRowIndex = rowPtr->getLastElementIndex();
    if(lastRowIndex > maxRowIndex) {
        maxRowIndex = lastRowIndex;
    }
}

size_t Table::ColumnsCountFinder::getColumnsCount() const noexcept {
    return maxRowIndex + 1;
}

size_t Table::getRowsCount() const noexcept {
    if(!tableRows.isEmpty()) {
        return tableRows.getLastElementIndex() + 1;
    }
    return 0;
}

size_t Table::getColumnsCount() const noexcept {
    if(getRowsCount() > 0) {
        ColumnsCountFinder columnsCountFinder;
        tableRows.forEach(columnsCountFinder);
        return columnsCountFinder.getColumnsCount();
    }
    return 0;
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
    size_t index = rowPtr->getLastElementIndex();
    while(isEmptyCell(rowPtr->getElement(index))) {
        rowPtr->removeElement(index);
        index = rowPtr->getLastElementIndex();
    }
}

void Table::edit(const TableIndex& index, CellPtr cellPtr) {
    RowPtr rowPtr;
    const size_t row = index.getRow();
    const size_t column = index.getColumn();
    const bool isTableCellEmptyCell = isEmptyCell(cellPtr);
    try {
        rowPtr = tableRows[row];
    } catch(Exception& error) {
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
        } catch(OperationNotPermitted& error) {
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
    } catch(Exception& error) {
        return EmptyCell::obtainRef();
    }
    CellPtr cellPtr;
    try {
        cellPtr = rowPtr->getElement(index.getColumn());
    } catch(Exception& error) {
        return EmptyCell::obtainRef();
    }
    return *cellPtr;
}