#include "ErrorCell.h"
#include "../SingletonCell/SingletonCellDefinition.mcrs"

SINGLETON_CELL_DEFINITION(ErrorCell);

const char* ErrorCell::valueString = "#ERROR!";

ErrorCell::ErrorCell(const char* string, size_t length) noexcept
: TableCell{}, value{string, length} {}


ErrorCell::ErrorCell() noexcept
: ErrorCell{valueString, 7} {}

const Number& ErrorCell::getValueAsNumber() const noexcept {
    return Number::getAdditionNeutralElement();
}

size_t ErrorCell::calculateOutputLength() const noexcept {
    return value.length();
}

size_t ErrorCell::calculateSerializedLength() const noexcept {
    return calculateOutputLength();
}