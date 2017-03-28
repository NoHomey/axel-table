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

bool utils::numberTextUtils::isDigit(const char symbol) noexcept {
    return (symbol >= '0') && (symbol <= '9');
}

bool utils::numberTextUtils::matchesNumberFirstSymbol(const char symbol) noexcept {
    return isPlusMinus(symbol) || isDigit(symbol);
}

unsigned int utils::numberTextUtils::toDigit(const char symbol) noexcept {
    return isDigit(symbol) ? (symbol - '0') : symbol;
}