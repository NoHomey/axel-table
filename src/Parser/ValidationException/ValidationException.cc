#include "ValidationException.h"

InvalidSymbolAtPosition::InvalidSymbolAtPosition(const size_t pos) noexcept
: position{pos} {}

size_t InvalidSymbolAtPosition::getPosition() const noexcept {
    return position;
}

InvalidSymbol::InvalidSymbol(const size_t pos, const char sym) noexcept
: InvalidSymbolAtPosition{pos}, symbol{sym} {}

char InvalidSymbol::getSymbol() const noexcept {
    return symbol;
}