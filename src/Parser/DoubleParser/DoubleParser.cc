#include "DoubleParser.h"
#include "../IntegerParser/IntegerParser.h"
#include "../ValidationException/ValidationException.h"
#include "../numberTextUtils/numberTextUtils.h"
#include "../IntegerExtractor/IntegerExtractor.h"

const size_t DoubleParser::TOTAL_DIGITS_COUNT = 15;

DoubleParser::DoubleParser(ConstString& string) noexcept
: TypeParser<double>{string} {}

double DoubleParser::parseFloatingPart(const size_t floatingPartBeginning) const noexcept {
    long long floatingPart = 0;
    unsigned long long floatingExponent = 1;
    size_t index = floatingPartBeginning;
    char currentSymbol = token[index];
    while(currentSymbol != '\0') {
        if((floatingPart != 0) || (!numberTextUtils::isZero(currentSymbol))) {
            floatingPart *= 10;
            floatingPart += numberTextUtils::toDigit(currentSymbol);
        }
        floatingExponent *= 10;
        ++index;
        currentSymbol = token[index];
    }
    return static_cast<double>(floatingPart) / static_cast<double>(floatingExponent);
}

double DoubleParser::typeParser() const {
    IntegerParser integerParser = {token};
    try {
        integerParser.validateType();
    } catch(const parse_exception::InvalidSymbol&) {
        IntegerExtractor extractor = {token};
        double floatingPart = parseFloatingPart(extractor.getExtractionEnd() + 1);
        if(numberTextUtils::isMinus(token[0])) {
            floatingPart *= -1;
        }

        return static_cast<double>(extractor.getInteger()) + floatingPart;
    }
    throw parse_exception::ParsedAsInteger{integerParser.parseType()};
}

void DoubleParser::typeValidator() const {
    const unsigned int firstDigit = static_cast<unsigned int>(numberTextUtils::isPlusMinus(token[0]));
    const bool isFirstDigitFloatingPoint = token[firstDigit] == '.';
    if(isFirstDigitFloatingPoint && (token[firstDigit + 1] == '\0')) {
        throw parse_exception::SingleFloatingPoint{};
    }
    try {
        IntegerParser{token}.validateType();
    } catch(const parse_exception::InvalidSymbol& error) {
        if(error.getSymbol() != '.') {
            throw error;
        }
        const size_t afterFloatingPoint = error.getPosition() + 1;
        if(token[afterFloatingPoint] == '\0') {
            throw parse_exception::IncompleteDouble{};
        }
        size_t floatingPartLength;
        try {
            floatingPartLength = numberTextUtils::containsOnlyDigits({token, afterFloatingPoint});
        } catch(const parse_exception::InvalidSymbol& error) {
            throw parse_exception::InvalidSymbol{error.getPosition() + afterFloatingPoint, error.getSymbol()};
        }
        if(isFirstDigitFloatingPoint) {
            throw parse_exception::DoubleHasNoIntegerPart{};
        }
        const size_t zerosCount = numberTextUtils::skipZeros({token, firstDigit});
        const size_t integerPartLength = afterFloatingPoint - 1 - firstDigit - zerosCount;
        const size_t totalDigitsCount = integerPartLength + floatingPartLength;
        if(totalDigitsCount > TOTAL_DIGITS_COUNT) {
            throw parse_exception::LossOfPrecision{};
        }
    }
}