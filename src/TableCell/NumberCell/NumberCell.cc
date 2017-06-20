#include "NumberCell.h"

NumberCell::NumberCell(const Number& number) noexcept
: value{number} {}

const Number& NumberCell::getValueAsNumber() const noexcept {
    return value;
}