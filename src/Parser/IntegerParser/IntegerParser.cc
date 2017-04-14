#include "IntegerParser.h"
#include "../ValidationException/ValidationException.h"
#include "../../utils/numberTextUtils/numberTextUtils.h"

const StringObject IntegerParser::ABS_MAX_VALUE = {"2147483647"};

const size_t IntegerParser::ABS_MAX_VALUE_LENGTH = 10;

IntegerParser::IntegerParser(const StringObject& string) noexcept
: TypeParser<int>{string} {}

int IntegerParser::parser() const {
    const size_t firstDigit = utils::numberTextUtils::isPlusMinus(token[0]) ? 1 : 0;
    const bool isNegative = utils::numberTextUtils::isMinus(token[0]);
    int result = 0;
    size_t i = firstDigit;
    while(token[i] != '\0') {
        result *= 10;
        result += utils::numberTextUtils::toDigit(token[i]);
        ++i;
    }

    return isNegative ? (-result) : result;
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
    bool isZeroException = false;
    size_t leadingZerosCount = 0;
    if(utils::numberTextUtils::isZero(token[firstDigit]) && (token[firstDigit + 1] != '\0')) {
        isZeroException = true;
        leadingZerosCount = 1;
        while(token[leadingZerosCount + firstDigit] == '0') {
            leadingZerosCount += 1;
        }
    }
    while(token[index] != '\0') {
        if(!utils::numberTextUtils::isDigit(token[index])) {
            throw parse_exception::InvalidSymbol(index, token[index]);
        }
        ++index;
    }
    if(isFirstSymbolSignSymbol && (index == 1)) {
        throw parse_exception::SingleSign(token[0]);
    }
    if(isZeroException) {
        throw parse_exception::LeadingZero(firstDigit, leadingZerosCount);
    }
    if(index >= maxLength) {
        if(ABS_MAX_VALUE < StringObject{token.cString() + firstDigit}) {
            throw parse_exception::Limit(index, token[index]);
        }
    }
}