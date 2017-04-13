#include "ValidationException.h"

parse_exception::ValidationException::ValidationException(const size_t pos, const char sym) noexcept
: Exception{}, position{pos}, symbol{sym} {}

size_t parse_exception::ValidationException::getPosition() const noexcept {
    return position;
}

char parse_exception::ValidationException::getSymbol() const noexcept {
    return symbol;
}

parse_exception::InValid::InValid(const size_t pos, const char sym) noexcept
: ValidationException{pos, sym} {}

parse_exception::Warnning::Warnning(const size_t pos, const char sym) noexcept
: ValidationException{pos, sym} {}