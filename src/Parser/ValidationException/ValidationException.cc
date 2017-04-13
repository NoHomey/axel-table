#include "ValidationException.h"

parse_exception::ValidationException::ValidationException(const size_t pos, const char sym) noexcept
: Exception{}, position{pos}, symbol{sym} {}

size_t parse_exception::ValidationException::getPosition() const noexcept {
    return position;
}

char parse_exception::ValidationException::getSymbol() const noexcept {
    return symbol;
}

parse_exception::Invalid::Invalid(const size_t pos, const char sym) noexcept
: ValidationException{pos, sym} {}

parse_exception::Empty::Empty() noexcept
: Invalid{0, '\0'} {}

parse_exception::Null::Null() noexcept
: Invalid{0, '\0'} {}

parse_exception::NoDigit::NoDigit(const char sym) noexcept
: Invalid{1, sym} {}

parse_exception::InvalidSymbol::InvalidSymbol(const size_t pos, const char sym) noexcept
: Invalid{pos, sym} {}

parse_exception::Warning::Warning(const size_t pos, const char sym) noexcept
: ValidationException{pos, sym} {}

parse_exception::Limit::Limit(const size_t pos, const char sym) noexcept
: Warning{pos, sym} {}

parse_exception::LeadingZero::LeadingZero(const size_t pos) noexcept
: Warning{pos, '0'} {}