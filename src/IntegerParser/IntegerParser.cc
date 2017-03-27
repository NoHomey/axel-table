#include "IntegerParser.h"
#include <cstdio>

IntegerParser::IntegerParser(const char* token) noexcept
: TypeParser<int>{token} {}

int IntegerParser::parse() const noexcept {
    return 0;
}

bool IntegerParser::matchesType() const noexcept {
    if(!((token[0] == '+') || (token[0] == '-') || ((token[0] >= '0') && (token[0] <= '9')))) {
        return false;
    }

    int i = 1;
    while(token[i] != '\0') {
        if((token[i] < '0') || (token[i] > '9')) {
            return false;
        }
        ++i;
    }

    return true;
}

bool IntegerParser::isValid() const noexcept {
    return false;
}