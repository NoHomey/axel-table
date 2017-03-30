#include "IntegerParser.h"
#include "../../utils/numberTextUtils/numberTextUtils.h"

IntegerParser::IntegerParser(const StringObject& string) noexcept
: token{const_cast<StringObject&>(string)} {}

int IntegerParser::parse() const noexcept {
    return 0;
}

bool IntegerParser::matchesType() const noexcept {
if(!utils::numberTextUtils::matchesNumberFirstSymbol(token[0])) {
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