#include "NumberParser.h"
#include "../ValidationException/ValidationException.h"

bool NumberParser::isMinus(const char symbol) noexcept {
    return symbol == '-';
}

bool NumberParser::isPlus(const char symbol) noexcept {
    return symbol == '+';
}

bool NumberParser::isPlusMinus(const char symbol) noexcept {
    return isPlus(symbol) || isMinus(symbol);
}

bool NumberParser::isFloatingPoint(const char symbol) noexcept {
    return symbol == '.';
}

bool NumberParser::isZero(const char symbol) noexcept {
    return symbol == '0';
}


bool NumberParser::isDigit(const char symbol) noexcept {
    return (symbol >= '0') && (symbol <= '9');
}

unsigned int NumberParser::toDigit(const char symbol) noexcept {
    return isDigit(symbol) ? (symbol - '0') : symbol;
}

size_t NumberParser::skipZeros(ConstString& string) noexcept {
    size_t index = 0;
    while(isZero(string[index])) {
        ++index;
    }

    return index;
}

size_t NumberParser::containsOnlyDigits(ConstString& string, const size_t offset) {
    size_t index = 0;
    char symbol = string[index];
    while(symbol != '\0') {
        if(!isDigit(symbol)) {
            throw parse_exception::InvalidSymbol{index + offset, symbol};
        }
        ++index;
        symbol = string[index];
    }

    return index;
}

size_t NumberParser::getFirstNoneZeroDigitPosition() const {
    const size_t firstDigit = NumberParser::isPlusMinus(token[0]) ? 1 : 0;
    const char firstDigitSymbol = token[firstDigit];
    if(firstDigitSymbol == '\0') {
        throw parse_exception::SingleSign{};
    }
    if(isFloatingPoint(firstDigitSymbol)) {
        if(token[firstDigit + 1] == '\0') {
            throw parse_exception::SingleFloatingPoint{};
        }
        throw parse_exception::DoubleHasNoIntegerPart{};
    }

    return firstDigit + skipZeros({token, firstDigit});
}

size_t NumberParser::getFloatingPointPosition() const noexcept {
    size_t index = 0;
    char symbol = token[index];
    while(symbol != '\0') {
        if(isFloatingPoint(symbol)) {
            return index;
        }
        ++index;
        symbol = token[index];
    }

    return index;
}

long long NumberParser::parseInteger(ConstString& string) noexcept {
    const bool isNegative = isMinus(string[0]);
    const size_t firstDigit = (isNegative || isPlus(string[0])) ? 1 : 0;
    size_t index = firstDigit + skipZeros({string, firstDigit});
    char symbol = string[index];
    long long integer = 0;
    while(symbol != '\0') {
        integer *= 10;
        integer += toDigit(symbol);
        ++index;
        symbol = string[index];
    }

    return isNegative ? (-integer) : integer;
}

NumberParser::NumberParser(ConstString& string) noexcept
: TypeParser<Number>{string} {}

Number NumberParser::typeParser() const {
    const size_t floatingPointPosition = getFloatingPointPosition();
    const size_t tokenLength = token.length();
    if(floatingPointPosition == tokenLength) {
        return {parseInteger(token)};
    }
    const size_t countOfZerosAfterFloatingPoint = skipZeros({token, floatingPointPosition + 1});
    long long integerPart = parseInteger({token.cString(), floatingPointPosition});
    if((floatingPointPosition + countOfZerosAfterFloatingPoint + 1) == tokenLength) {
        return {integerPart};
    }

    return {};
}

void NumberParser::typeValidator() const {
    const size_t firstNoneZeroDigitPosition = getFirstNoneZeroDigitPosition();
    const size_t tokenLength = token.length();
    if(firstNoneZeroDigitPosition == tokenLength) {
        return;
    }
    ConstString tokenFromFirstDigit = {token, firstNoneZeroDigitPosition};
    size_t integerPartLength = 0;
    size_t floatingPartLength = 0;
    try {
        integerPartLength = containsOnlyDigits(tokenFromFirstDigit, firstNoneZeroDigitPosition);
    } catch(const parse_exception::InvalidSymbol& error) {
        integerPartLength = error.getPosition() - firstNoneZeroDigitPosition;
        if(!isFloatingPoint(error.getSymbol())) {
            throw error;
        }
        const size_t positionAfterFloatingPoint = error.getPosition() + 1;
        if(token[positionAfterFloatingPoint] == '\0') {
            throw parse_exception::IncompleteDouble{};
        }
        const size_t countOfZerosAfterFloatingPoint = skipZeros({token, positionAfterFloatingPoint});
        const size_t positionOfFirstNoneZeroDigitAfterFloatingPoint =
                positionAfterFloatingPoint + countOfZerosAfterFloatingPoint;
        if(positionOfFirstNoneZeroDigitAfterFloatingPoint < tokenLength) {
            floatingPartLength = containsOnlyDigits(
                {token, positionOfFirstNoneZeroDigitAfterFloatingPoint},
                positionOfFirstNoneZeroDigitAfterFloatingPoint
            ) + countOfZerosAfterFloatingPoint;
        }
    }
    if((integerPartLength + floatingPartLength) > MAXIMUM_OF_DIGITS_COUNT) {
        throw parse_exception::NumberIsTooLong{};
    }
}