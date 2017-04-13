#include "IntegerParser.h"
#include "../../utils/numberTextUtils/numberTextUtils.h"
#include <iostream>

IntegerParser::IntegerParser(const StringObject& string) noexcept
: token{string} {}

int IntegerParser::parse() const noexcept {
    return 0;
}

bool IntegerParser::matchesType() const noexcept {
    if(!utils::numberTextUtils::matchesNumberBeginning(token[0], token[1])) {
        return false;
    }

    int i = 1;
    while(token[i] != '\0') {
        if(!utils::numberTextUtils::isDigit(token[i])) {
            return false;
        }
        ++i;
    }

    return true;
}

bool IntegerParser::isValid() const noexcept {
    return false;
}