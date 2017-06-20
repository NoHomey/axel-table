#include "StringNumberCell.h"

StringNumberCell::StringNumberCell(const Number& number) noexcept
: NumberCell{number} {}

size_t StringNumberCell::calculateOutputLength() const noexcept {
    return NumberCell::calculateOutputLength() + 2;
}