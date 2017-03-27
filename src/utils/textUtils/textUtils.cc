#include "textUtils.h"

bool utils::textUtils::isMinus(const char symbol) noexcept {
    return symbol == '-';
}

bool utils::textUtils::isPlus(const char symbol) noexcept {
    return symbol == '+';
}

bool utils::textUtils::isDigit(const char symbol) noexcept {
    return (symbol >= '0') && (symbol <= '9');
}