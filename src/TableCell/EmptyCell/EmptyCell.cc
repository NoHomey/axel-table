#include "EmptyCell.h"

const Number EmptyCell::emptyCellNumberValue = {};

EmptyCell EmptyCell::instance = {};

const EmptyCell& EmptyCell::obtainEmptyCellRef() noexcept {
    return instance;
}

const EmptyCell* EmptyCell::obtainEmptyCellConstPtr() noexcept {
    return obtainEmptyCellPtr();
}

EmptyCell* EmptyCell::obtainEmptyCellPtr() noexcept {
    return &instance;
}

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