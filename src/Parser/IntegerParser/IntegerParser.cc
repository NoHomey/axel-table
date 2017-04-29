#include "IntegerParser.h"
#include "../ValidationException/ValidationException.h"
#include "../numberTextUtils/numberTextUtils.h"

ConstString IntegerParser::ABS_MAX_VALUE = {"9223372036854775807"};

const size_t IntegerParser::ABS_MAX_VALUE_LENGTH = 19;

IntegerParser::IntegerParser(ConstString& string) noexcept
: TypeParser<long long>{string} {}

long long IntegerParser::typeParser() const {
    const bool isNegative = numberTextUtils::isMinus(token[0]);
    const size_t firstDigit = isNegative || numberTextUtils::isPlus(token[0]) ? 1 : 0;
    long long result = 0;
    size_t index = firstDigit + numberTextUtils::skipZeros(token.cString() + firstDigit);
    while(token[index] != '\0') {
        result *= 10;
        result += numberTextUtils::toDigit(token[index]);
        ++index;
    }

    return isNegative ? (-result) : result;
}

void IntegerParser::typeValidator() const {
    const bool isFirstSymbolSignSymbol = numberTextUtils::isPlusMinus(token[0]);
    const size_t firstDigit = isFirstSymbolSignSymbol ? 1 : 0; 
    const size_t firstNoneZero = firstDigit + numberTextUtils::skipZeros(token.cString() + firstDigit);
    const size_t maxLength = ABS_MAX_VALUE_LENGTH + firstNoneZero;
    const char* tokenFromFirstDigit = token.cString() + firstNoneZero;
    size_t length;
    try {
        length = firstNoneZero + numberTextUtils::containsOnlyDigits(tokenFromFirstDigit);
    } catch(const parse_exception::InvalidSymbol& error) {
        throw parse_exception::InvalidSymbol(error.getPosition() + firstNoneZero, error.getSymbol());
    }
    if(isFirstSymbolSignSymbol && (length == 1)) {
        throw parse_exception::SingleSign();
    }
    if((length >= maxLength) && (ABS_MAX_VALUE < ConstString{tokenFromFirstDigit})) {
        numberTextUtils::throwLimitException(token[0]);
    }
}