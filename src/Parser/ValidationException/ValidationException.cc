#include "ValidationException.h"

parse_exception::InvalidSymbolAtPosition::InvalidSymbolAtPosition(const size_t pos) noexcept
: position{pos} {}

size_t parse_exception::InvalidSymbolAtPosition::getPosition() const noexcept {
    return position;
}

parse_exception::NotEscapedQuotes::NotEscapedQuotes(const size_t pos) noexcept
: InvalidSymbolAtPosition{pos} {}

parse_exception::AloneBackslash::AloneBackslash(const size_t pos) noexcept
: InvalidSymbolAtPosition{pos} {}

parse_exception::InvalidSymbol::InvalidSymbol(const size_t pos, const char sym) noexcept
: InvalidSymbolAtPosition{pos}, symbol{sym} {}

char parse_exception::InvalidSymbol::getSymbol() const noexcept {
    return symbol;
}