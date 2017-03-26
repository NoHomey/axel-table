#include "TableCell.h"

TableCell::TableCell() {}

TableCell::TableCell(int value) {}

bool TableCell::isEmpty() const {
	return true;
}

bool TableCell::isInteger() const {
	return false;
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
