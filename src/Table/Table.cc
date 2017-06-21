#include "Table.h"
#include "../TableCell/EmptyCell/EmptyCell.h"

Table::TableIndex::TableIndex(size_t row, size_t col) noexcept
: rowIndex{row}, columnIndex{col} {}

size_t Table::TableIndex::getRow() const noexcept {
    return rowIndex;
}

size_t Table::TableIndex::getColumn() const noexcept {
    return columnIndex;
}

void Table::edit(const TableIndex& index, CellPtr cellValue) {
    RowPtr rowPtr;
    try {
        rowPtr = rows[index.getRow()];
    } catch(Exception& error) {
        rowPtr = new Row;
        rows.setElement(rowPtr, index.getRow());
    }
    rowPtr->setElement(cellValue, index.getColumn());
}

const TableCell& Table::operator[](const TableIndex& index) const {
    RowPtr rowPtr;
    try {
        rowPtr = rows[index.getRow()];
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