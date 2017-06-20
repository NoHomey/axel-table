#include "NumberCell.h"
#include "../../../dependencies/fpconv/src/fpconv.h"
#include "../../shared_constants.h"

char NumberCell::fpconv_buffer[24];

NumberCell::NumberCell(const Number& number) noexcept
: value{number} {}

const Number& NumberCell::getValueAsNumber() const noexcept {
    return value;
}

size_t NumberCell::calculateIntegerOutputLength() const noexcept {
    long long integerValue = value.getInteger();
    if(integerValue == 0) {
        return 1;
    }
    const bool isNegative = integerValue < 0;
    size_t length = 0;
    while(integerValue != 0) {
        integerValue /= 10;
        ++length;
    }
    if(length > MAXIMUM_OF_DIGITS_COUNT) {
        length = MAXIMUM_OF_DIGITS_COUNT;
    }
    return length + isNegative;
}

size_t NumberCell::calculateRealOutputLength() const noexcept {
    size_t length = fpconv_dtoa(value.getReal(), fpconv_buffer);
    bool includesFloatingPoint = false;
    const bool isNegative = fpconv_buffer[0] == '-';
    for(size_t index = isNegative; index < length; ++index) {
        if(fpconv_buffer[index] == '.') {
            includesFloatingPoint = true;
            break;
        }
    }
    const size_t maxLength = MAXIMUM_OF_DIGITS_COUNT + includesFloatingPoint + isNegative;
    if(length > maxLength) {
        length = maxLength;
    }
    return length;
}

size_t NumberCell::calculateOutputLength() const noexcept {
    return value.isInteger() ? calculateIntegerOutputLength() : calculateRealOutputLength();
}

size_t NumberCell::calculateSerializedLength() const noexcept {
    return calculateOutputLength();
}