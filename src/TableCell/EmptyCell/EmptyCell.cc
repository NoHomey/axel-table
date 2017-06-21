#include "EmptyCell.h"
#include "../SingletonCell/SingletonCellDefinition.mcrs"

SINGLETON_CELL_DEFINITION(EmptyCell);

EmptyCell::EmptyCell() noexcept
: TableCell{} {}

const Number& EmptyCell::getValueAsNumber() const noexcept {
    return Number::getAdditionNeutralElement();
}

size_t EmptyCell::calculateOutputLength() const noexcept {
    return 0;
}

size_t EmptyCell::calculateSerializedLength() const noexcept {
    return 0;
}

bool EmptyCell::isDeletable() const noexcept {
    return false;
}