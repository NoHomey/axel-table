#include "DoubleParser.h"
#include "../IntegerParser/IntegerParser.h"
#include "../ValidationException/ValidationException.h"
#include "../numberTextUtils/numberTextUtils.h"
#include "../IntegerExtractor/IntegerExtractor.h"

const size_t DoubleParser::TOTAL_DIGITS_COUNT = 15;

DoubleParser::DoubleParser(ConstString& string) noexcept
: TypeParser<double>{string} {}

double DoubleParser::typeParser() const {
    IntegerExtractor extractor = {token};
    unsigned long long floatingExponent = 1;
    long long floating = 0;
    size_t index = extractor.getExtractionEnd() + 1;
    char symbol = token[index];
    while(symbol != '\0') {
        if((floating != 0) || (!numberTextUtils::isZero(symbol))) {
            floating *= 10;
            floating += numberTextUtils::toDigit(symbol);
        }
        floatingExponent *= 10;
        ++index;
        symbol = token[index];
    }
    if(numberTextUtils::isMinus(token[0])) {
        floating *= -1;
    }
    const double floatingPart = static_cast<double>(floating) / static_cast<double>(floatingExponent);

    return static_cast<double>(extractor.getInteger()) + floatingPart;
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
        const char* tokenAsCString = token.cString();
        size_t floatingPartLength;
        try {
            ConstString tokenAfterFloatingPoint = {tokenAsCString + floatingPoint};
            floatingPartLength = numberTextUtils::containsOnlyDigits(tokenAfterFloatingPoint);
        } catch(const parse_exception::InvalidSymbol& error) {
            throw parse_exception::InvalidSymbol{error.getPosition() + floatingPoint, error.getSymbol()};
        }
        const unsigned int firstDigit = static_cast<unsigned int>(numberTextUtils::isPlusMinus(token[0]));
        ConstString tokenFromFirstDigit = {tokenAsCString + firstDigit};
        const size_t zerosCount = numberTextUtils::skipZeros(tokenFromFirstDigit);
        const size_t wholePartLength = floatingPoint - 1 - firstDigit - zerosCount;
        const size_t totalDigitsCount = wholePartLength + floatingPartLength;
        if(totalDigitsCount > TOTAL_DIGITS_COUNT) {
            numberTextUtils::throwLimitException(token[0]);
        }
        return;
    }
    throw parse_exception::ParsedAsInteger{integerValue};
}