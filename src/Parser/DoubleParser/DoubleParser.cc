#include "DoubleParser.h"
#include "../IntegerParser/IntegerParser.h"
#include "../ValidationException/ValidationException.h"
#include "../numberTextUtils/numberTextUtils.h"

const size_t DoubleParser::TOTAL_DIGITS_COUNT = 15;

DoubleParser::DoubleParser(ConstString& string) noexcept
: TypeParser<double>{string} {}

double DoubleParser::typeParser() const {
    return 0;
}

void DoubleParser::typeValidator() const {
    IntegerParser integerParser = {token};
    long long integerValue;
    try {
        integerValue = integerParser.parseType();
    } catch(const parse_exception::InvalidSymbol& error) {
        if(error.getSymbol() != '.') {
            throw error;
        }
        const size_t floatingPoint = error.getPosition() + 1;
        size_t floatingPartLength;
        try {
            floatingPartLength = numberTextUtils::containsOnlyDigits(token.cString() + floatingPoint);
        } catch(const parse_exception::InvalidSymbol& error) {
            throw parse_exception::InvalidSymbol(error.getPosition() + floatingPoint, error.getSymbol());
        }
        const unsigned int firstDigit = static_cast<unsigned int>(numberTextUtils::isPlusMinus(token[0]));
        const size_t zerosCount = numberTextUtils::skipZeros(token.cString() + firstDigit);
        const size_t wholePartLength = floatingPoint - 1 - firstDigit - zerosCount;
        const size_t totalDigitsCount = wholePartLength + floatingPartLength;
        if(totalDigitsCount > TOTAL_DIGITS_COUNT) {
            numberTextUtils::throwLimitException(token[0]);
        }
        return;
    }
    throw parse_exception::ParsedAsInteger(integerValue);
}