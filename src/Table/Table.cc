#include "Table.h"
#include "../TableCell/EmptyCell/EmptyCell.h"

Table::~Table() noexcept {
    tableRows.forEach([](const Row* rowPtr, size_t) noexcept {
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
    if(tableRows.isEmpty()) {
        return 0;
    }
    const size_t lastRowIndex = tableRows.getLastElementIndex();
    if(tableRows.getElement(lastRowIndex)->length() > 0) {
        return lastRowIndex + 1;
    }
    size_t rowsCount = 0;
    tableRows.forEach([&rowsCount](const Row* rowPtr, size_t index) noexcept {
        if(rowPtr->length() > 0) {
            rowsCount = index + 1;
        }
    });
    return rowsCount;
}

size_t Table::getColumnsCount() const noexcept {
    size_t columnsCount = 0;
    tableRows.forEach([&columnsCount](const Row* rowPtr, size_t) noexcept {
        const size_t rowLength = rowPtr->length();
        if(rowLength > columnsCount) {
            columnsCount = rowLength;
        }
    });
    return columnsCount;
}

void Table::edit(const TableIndex& index, const TableCell* cellPtr) {
    Row* rowPtr;
    const size_t row = index.getRow();
    if(tableRows.hasElementAt(row)) {
        rowPtr = tableRows.getElement(row);
    } else {
        if(EmptyCell::isEmptyCell(cellPtr)) {
            return;
        }
        rowPtr = new Row;
        tableRows.setElement(row, rowPtr);
    }
    rowPtr->edit(index.getColumn(), cellPtr);
}

const TableCell* Table::operator[](const TableIndex& index) const {
    const size_t row = index.getRow();
    if(!tableRows.hasElementAt(row)) {
        return EmptyCell::obtainPtr();
    }
    return tableRows.getElement(row)->cellAt(index.getColumn());
}