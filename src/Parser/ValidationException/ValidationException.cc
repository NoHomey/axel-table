#include "ValidationException.h"

parse_exception::InvalidSymbol::InvalidSymbol(const size_t pos, const char sym) noexcept
: Invalid{}, position{pos}, symbol{sym} {}

size_t parse_exception::InvalidSymbol::getPosition() const noexcept {
    return position;
}

char parse_exception::InvalidSymbol::getSymbol() const noexcept {
    return symbol;
}