#include "IntegerParser.h"

IntegerParser::IntegerParser(const char* token) noexcept
: TypeParser<int>{token} {}

int IntegerParser::parse() const noexcept {
    return 0;
}

bool IntegerParser::matchesType() const noexcept {
    return false;
}

bool IntegerParser::isValid() const noexcept {
    return false;
}