#include "NumberParser.h"
#include "../ValidationException/ValidationException.h"
#include "../numberTextUtils/numberTextUtils.h"

NumberParser::NumberParser(ConstString& string) noexcept
: TypeParser<Number>{string} {}

Number NumberParser::typeParser() const {
    return {};
}

void NumberParser::typeValidator() const {
    const size_t firstDigit = numberTextUtils::isPlusMinus(token[0]) ? 1 : 0;
    size_t firstNoneZero;
    try {
        firstNoneZero = firstDigit + numberTextUtils::skipZeros({token, firstDigit});
    } catch(const BadStringOffset& error) {
        throw parse_exception::SingleSign{};
    }
    const bool isFirstDigitFloatingPoint = token[firstDigit] == '.';
    if(isFirstDigitFloatingPoint && (token[firstDigit + 1] == '\0')) {
        throw parse_exception::SingleFloatingPoint{};
    }
}