#include "Table.h"
#include "../TableCell/EmptyCell/EmptyCell.h"

void Table::deleteCellsInRow(CellPtr cellPtr, size_t) noexcept {
    if(cellPtr->isDeletable()) {
        delete cellPtr;
    }
}

void Table::deleteRow(const RowPtr rowPtr, size_t) noexcept {
    rowPtr->forEach(deleteCellsInRow);
    delete rowPtr;
}

Table::~Table() noexcept {
    rows.forEach(deleteRow);
}

Table::TableIndex::TableIndex(size_t row, size_t col) noexcept
: rowIndex{row}, columnIndex{col} {}

size_t Table::TableIndex::getRow() const noexcept {
    return rowIndex;
}

size_t Table::TableIndex::getColumn() const noexcept {
    return columnIndex;
}

void Table::clean(const RowPtr rowPtr, size_t index) noexcept {
    CellPtr cellPtr;
    try {
        cellPtr = rowPtr->getElement(index);
    } catch (Exception& error) {
        cellPtr = EmptyCell::obtainPtr();
    }
    if(cellPtr->isDeletable()) {
        delete cellPtr;
    }
}

void Table::edit(const TableIndex& index, CellPtr cellValue) {
    RowPtr rowPtr;
    const size_t row = index.getRow();
    const size_t column = index.getColumn();
    try {
        rowPtr = rows[row];
    } catch(Exception& error) {
        rowPtr = new Row;
        rows.setElement(rowPtr, row);
    }
    clean(rowPtr, column);
    rowPtr->setElement(cellValue, column);
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