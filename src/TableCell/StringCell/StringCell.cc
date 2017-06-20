#include "StringCell.h"
#include <utility>

const Number StringCell::stringNumberValue = {};

StringCell::StringCell(FixedSizeString&& string) noexcept
: value{std::move(string)} {}

const Number& StringCell::getValueAsNumber() const noexcept {
    return stringNumberValue;
}