#include "StringCell.h"
#include <utility>

const Number StringCell::stringNumberValue = {};

StringCell::StringCell(FixedSizeString&& string) noexcept
: TableCell{}, value{std::move(string)} {}

const Number& StringCell::getValueAsNumber() const noexcept {
    return stringNumberValue;
}

size_t StringCell::calculateOutputLength() const noexcept {
    return value.length();
}

bool StringCell::shouldBeEscaped(char symbol) noexcept {
    return (symbol == '"') || (symbol == '\\');
}

size_t StringCell::calculateNumberOfCharsToBeEscaped() const noexcept {
    size_t count = 0;
    const size_t length = value.length();
    for(size_t index = 0; index < length; ++index) {
        if(shouldBeEscaped(value[index])) {
            ++count;
        }
    }
    return count;
}

size_t StringCell::calculateSerializedLength() const noexcept {
    return value.length() + calculateNumberOfCharsToBeEscaped() + 2;
}