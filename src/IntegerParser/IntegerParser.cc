#include "IntegerParser.h"
#include "../utils/textUtils/textUtils.h"
#include <cstdio>

IntegerParser::IntegerParser(const char* token) noexcept
: TypeParser<int>{token} {}

int IntegerParser::parse() const noexcept {
    return 0;
}

bool IntegerParser::matchesType() const noexcept {
    using namespace utils::textUtils;
    
    const bool matchFirstSymbol = isMinus(token[0]) || isPlus(token[0]) || isDigit(token[0]);
    if(!matchFirstSymbol) {
        return false;
    }

    int i = 1;
    while(token[i] != '\0') {
        if(!isDigit(token[i])) {
            return false;
        }
        ++i;
    }

    return true;
}

bool IntegerParser::isValid() const noexcept {
    return false;
}