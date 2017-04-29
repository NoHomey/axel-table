#include "TableCell.h"

TableCell TableCell::ErrorCell() noexcept {
	TableCell cell;
	cell.cellType = TableCellType::Error;

	return cell;
}

TableCell::TableCell() noexcept
: cellType{TableCellType::Empty}, cellValue{nullptr} {}

TableCell::TableCell(const long long value) noexcept
: cellType{TableCellType::Integer}, cellValue{nullptr} {
	cellValue.integerValue = value;
}

TableCell::TableCell(const double value) noexcept
: cellType{TableCellType::Double}, cellValue{nullptr} {
	cellValue.doubleValue = value;
}

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

long long TableCell::toInteger() const noexcept {
	if(isInteger()) {
		return cellValue.integerValue;
	}
	if(isDouble()) {
		return cellValue.doubleValue;
	}
	
	return 0;
}
