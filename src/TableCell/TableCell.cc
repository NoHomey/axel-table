#include "TableCell.h"

void TableCell::deleteIfDeletable(const TableCell* cellPtr) noexcept {
    if(cellPtr->isDeletable()) {
        delete cellPtr;
    }
}

bool TableCell::isDeletable() const noexcept {
    return true;
}