#include "numberTextUtils.h"

bool utils::numberTextUtils::isMinus(const char symbol) noexcept {
    return symbol == '-';
}

bool utils::numberTextUtils::isPlus(const char symbol) noexcept {
    return symbol == '+';
}

bool utils::numberTextUtils::isPlusMinus(const char symbol) noexcept {
    return isPlus(symbol) || isMinus(symbol);
}

bool utils::numberTextUtils::isZero(const char symbol) noexcept {
    return symbol == '0';
}


bool utils::numberTextUtils::isDigit(const char symbol) noexcept {
    return (symbol >= '0') && (symbol <= '9');
}

bool utils::numberTextUtils::matchesNumberBeginning(const char first, const char second) noexcept {
    if(isDigit(first)) {
        return true;
    }

    return isPlusMinus(first) && isDigit(second);
}

unsigned int utils::numberTextUtils::toDigit(const char symbol) noexcept {
    return isDigit(symbol) ? (symbol - '0') : symbol;
}