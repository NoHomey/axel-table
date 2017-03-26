#include "TableCell.h"

TableCell::TableCell()
: cellType{TableCellType::Empty} {}

TableCell::TableCell(const int value)
: cellType{TableCellType::Integer} {}

TableCell::TableCell(const double value) {}

bool TableCell::isEmpty() const {
	return cellType == TableCellType::Empty;
}

bool TableCell::isInteger() const {
	return cellType == TableCellType::Integer;
}

bool TableCell::isDouble() const {
	return false;
}

bool TableCell::isString() const {
	return false;
}

bool TableCell::isError() const {
	return false;
}
