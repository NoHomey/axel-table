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

template<typename Type>
parse_exception::ParsedAsDifferentType<Type>::ParsedAsDifferentType(const Type val) noexcept
: Exception{}, value{val} {}

template<typename Type>
Type parse_exception::ParsedAsDifferentType<Type>::getValue() const noexcept {
    return value;
}

template class parse_exception::ParsedAsDifferentType<long long>;

template class parse_exception::ParsedAsDifferentType<double>;