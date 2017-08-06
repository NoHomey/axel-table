#include "Row.h"
#include "../../TableCell/EmptyCell/EmptyCell.h"

Row::~Row() noexcept {
    cells.forEach([](const TableCell* cell, size_t) {
        TableCell::deleteIfDeletable(cell);
    });
}

size_t Row::length() const noexcept {
    return cells.isEmpty() ? 0 : cells.getLastElementIndex() + 1;
}

void Row::edit(size_t index, const TableCell* cellPtr) {
    const bool isEmpty = EmptyCell::isEmptyCell(cellPtr);
    if(cells.hasElementAt(index)) {
        TableCell::deleteIfDeletable(cells.getElement(index));
        if(isEmpty) {
            cells.removeElement(index);
            return;
        }
    }
    if(!isEmpty) {
        cells.setElement(index, cellPtr);
    }
}

const TableCell* Row::cellAt(const size_t index) const {
    if(cells.hasElementAt(index)) {
        return cells.getElement(index);
    }
    return EmptyCell::obtainPtr();
}