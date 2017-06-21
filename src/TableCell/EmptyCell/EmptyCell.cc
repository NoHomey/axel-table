#include "EmptyCell.h"
#include "../SingletonCell/SingletonCellDefinition.mcrs"

SINGLETON_CELL_DEFINITION(EmptyCell);

const Number EmptyCell::emptyCellNumberValue = {};

EmptyCell::EmptyCell() noexcept
: TableCell{} {}

const Number& EmptyCell::getValueAsNumber() const noexcept {
    return emptyCellNumberValue;
}

size_t EmptyCell::calculateOutputLength() const noexcept {
    return 0;
}

size_t EmptyCell::calculateSerializedLength() const noexcept {
    return 0;
}