#include "IntegerParser.h"
#include "../ValidationException/ValidationException.h"
#include "../../utils/numberTextUtils/numberTextUtils.h"

ConstString IntegerParser::ABS_MAX_VALUE = {"2147483647"};

const size_t IntegerParser::ABS_MAX_VALUE_LENGTH = 10;

IntegerParser::IntegerParser(ConstString& string) noexcept
: TypeParser<int>{string} {}

int IntegerParser::parser() const {
    const bool isNegative = utils::numberTextUtils::isMinus(token[0]);
    size_t index = isNegative || utils::numberTextUtils::isPlus(token[0]) ? 1 : 0;
    int result = 0;
    while(token[index] == '0') {
        ++index;
    }
    while(token[index] != '\0') {
        result *= 10;
        result += utils::numberTextUtils::toDigit(token[index]);
        ++index;
    }

    return isNegative ? (-result) : result;
}

void IntegerParser::validator() const {
    const bool isFirstSymbolSignSymbol = utils::numberTextUtils::isPlusMinus(token[0]);
    size_t firstDigit = isFirstSymbolSignSymbol ? 1 : 0; 
    while(token[firstDigit] == '0') {
        ++firstDigit;
    }
    const size_t maxLength = ABS_MAX_VALUE_LENGTH + firstDigit;
    size_t index = firstDigit;
    while(token[index] != '\0') {
        if(!utils::numberTextUtils::isDigit(token[index])) {
            throw parse_exception::InvalidSymbol(index, token[index]);
        }
        ++index;
    }
    if(isFirstSymbolSignSymbol && (index == 1)) {
        throw parse_exception::SingleSign(token[0]);
    }
    if(index >= maxLength) {
        if(ABS_MAX_VALUE < ConstString{token.cString() + firstDigit}) {
            throw parse_exception::Limit(index, token[index]);
        }
    }
}