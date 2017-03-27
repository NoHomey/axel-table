#include "TableCell.h"

TableCell TableCell::ErrorCell() noexcept {
	TableCell cell;
	cell.cellType = TableCellType::Error;

	return cell;
}

TableCell::TableCell() noexcept
: cellType{TableCellType::Empty} {}

TableCell::TableCell(const int value) noexcept
: cellType{TableCellType::Integer} {}

TableCell::TableCell(const double value) noexcept
: cellType{TableCellType::Double} {}

bool TableCell::isEmpty() const noexcept {
	return cellType == TableCellType::Empty;
}

bool TableCell::isInteger() const noexcept {
	return cellType == TableCellType::Integer;
}

bool TableCell::isDouble() const noexcept {
	return cellType == TableCellType::Double;
}

bool TableCell::isString() const noexcept {
	return false;
}

bool TableCell::isError() const noexcept {
	return cellType == TableCellType::Error;
}
