#include "numberTextUtils.h"
#include "../ValidationException/ValidationException.h"

bool numberTextUtils::isMinus(const char symbol) noexcept {
    return symbol == '-';
}

bool numberTextUtils::isPlus(const char symbol) noexcept {
    return symbol == '+';
}

bool numberTextUtils::isPlusMinus(const char symbol) noexcept {
    return isPlus(symbol) || isMinus(symbol);
}

bool numberTextUtils::isZero(const char symbol) noexcept {
    return symbol == '0';
}


bool numberTextUtils::isDigit(const char symbol) noexcept {
    return (symbol >= '0') && (symbol <= '9');
}

unsigned int numberTextUtils::toDigit(const char symbol) noexcept {
    return isDigit(symbol) ? (symbol - '0') : symbol;
}

size_t numberTextUtils::skipZeros(const char* string) noexcept {
    size_t index = 0;
    while(isZero(string[index])) {
        ++index;
    }

    return index;
}

size_t numberTextUtils::containsOnlyDigits(const char* string) {
    size_t index = 0;
    while(string[index] != '\0') {
        if(!isDigit(string[index])) {
            throw parse_exception::InvalidSymbol(index, string[index]);
        }
        ++index;
    }

    return index;
}

void numberTextUtils::throwLimitException(const char symbol) {
    if(isMinus(symbol)) {
        throw parse_exception::MinimumLimit();
    } else {
        throw parse_exception::MaximumLimit();
    }
}