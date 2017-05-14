#include "NumberCell.h"

NumberCell::NumberCell(const Number& number) noexcept
: value{number} {}

NumberCell::operator Number() const noexcept {
    return value;
}