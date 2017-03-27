#include "TableCell.h"

TableCell TableCell::ErrorCell() {
	TableCell cell;
	cell.cellType = TableCellType::Error;

	return cell;
}

TableCell::TableCell()
: cellType{TableCellType::Empty} {}

TableCell::TableCell(const int value)
: cellType{TableCellType::Integer} {}

TableCell::TableCell(const double value)
: cellType{TableCellType::Double} {}

bool TableCell::isEmpty() const {
	return cellType == TableCellType::Empty;
}

bool TableCell::isInteger() const {
	return cellType == TableCellType::Integer;
}

bool TableCell::isDouble() const {
	return cellType == TableCellType::Double;
}

bool TableCell::isString() const {
	return false;
}

bool TableCell::isError() const {
	return cellType == TableCellType::Error;
}
