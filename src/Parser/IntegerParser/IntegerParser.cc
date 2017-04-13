#include "IntegerParser.h"
#include "../ValidationException/ValidationException.h"
#include "../../utils/numberTextUtils/numberTextUtils.h"

const StringObject IntegerParser::ABS_MAX_VALUE = {"2147483647"};

const size_t IntegerParser::ABS_MAX_VALUE_LENGTH = 10;

IntegerParser::IntegerParser(const StringObject& string) noexcept
: TypeParser<int>{string} {}

int IntegerParser::parser() const {
    return 0;
}

bool IntegerParser::matchesType() const noexcept {
    const size_t firstDigit = utils::numberTextUtils::isPlusMinus(token[0]) ? 1 : 0;
    size_t i = firstDigit;
    while(token[i] != '\0') {
        if(!utils::numberTextUtils::isDigit(token[i])) {
            return false;
        }
        ++i;
    }

    return i > firstDigit;
}

void IntegerParser::validator() const {
    if(token.isEmpty()) {
        throw parse_exception::Empty();
    }
    if(token.isNull()) {
        throw parse_exception::Null();
    }
    const bool isFirstSymbolSignSymbol = utils::numberTextUtils::isPlusMinus(token[0]);
    const size_t firstDigit = isFirstSymbolSignSymbol ? 1 : 0;
    const size_t maxLength = ABS_MAX_VALUE_LENGTH + firstDigit;
    size_t index = firstDigit; 
    int isZeroException = -1;
    if(utils::numberTextUtils::isZero(token[index]) && (token[index + 1] != '\0')) {
        isZeroException = index;
    }
    while(token[index] != '\0') {
        if(!utils::numberTextUtils::isDigit(token[index])) {
            throw parse_exception::InvalidSymbol(index, token[index]);
        }
        ++index;
    }
    if(isFirstSymbolSignSymbol && (index == 1)) {
        throw parse_exception::NoDigit(token[0]);
    }
    if(isZeroException != -1) {
        throw parse_exception::LeadingZero(index);
    }
    if(index >= maxLength) {
        if(ABS_MAX_VALUE < StringObject{token.cString() + firstDigit}) {
            throw parse_exception::Limit(index, token[index]);
        }
    }
}