#include "IntegerParser.h"
#include "../ValidationException/ValidationException.h"
#include "../numberTextUtils/numberTextUtils.h"
#include "../IntegerExtractor/IntegerExtractor.h"

ConstString IntegerParser::ABS_MAX_VALUE = {"9223372036854775807", 19};

const size_t IntegerParser::ABS_MAX_VALUE_LENGTH = 19;

IntegerParser::IntegerParser(ConstString& string) noexcept
: TypeParser<long long>{string} {}

long long IntegerParser::typeParser() const {
    return IntegerExtractor{token}.getInteger();
}

void IntegerParser::typeValidator() const {
    const size_t firstDigit = numberTextUtils::isPlusMinus(token[0]) ? 1 : 0;
    size_t firstNoneZero;
    try {
        firstNoneZero = firstDigit + numberTextUtils::skipZeros({token, firstDigit});
    } catch(const BadStringOffset& error) {
        throw parse_exception::SingleSign{};
    }
    if(firstNoneZero == token.length()) {
        return;
    }
    ConstString tokenFromFirstDigit = {token, firstNoneZero};
    size_t length;
    try {
        length = numberTextUtils::containsOnlyDigits(tokenFromFirstDigit);
    } catch(const parse_exception::InvalidSymbol& error) {
        throw parse_exception::InvalidSymbol{error.getPosition() + firstNoneZero, error.getSymbol()};
    }
    if((length > ABS_MAX_VALUE_LENGTH) || ((length == ABS_MAX_VALUE_LENGTH) &&
                                        (ABS_MAX_VALUE < tokenFromFirstDigit))) {
        numberTextUtils::throwLimitException(token[0]);
    }
}