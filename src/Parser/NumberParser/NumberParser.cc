#include "NumberParser.h"

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
    char currentSymbol = string[index];
    while(currentSymbol != '\0') {
        if(!isDigit(currentSymbol)) {
            throw InvalidSymbol{index + offset, currentSymbol};
        }
        ++index;
        currentSymbol = string[index];
    }

    return index;
}

size_t NumberParser::getFirstNoneZeroDigitPosition() const {
    const size_t firstDigit = NumberParser::isPlusMinus(token[0]) ? 1 : 0;
    const char firstDigitSymbol = token[firstDigit];
    if(firstDigitSymbol == '\0') {
        throw SingleSign{};
    }
    if(isFloatingPoint(firstDigitSymbol)) {
        if(token[firstDigit + 1] == '\0') {
            throw SingleFloatingPoint{};
        }
        throw DoubleHasNoIntegerPart{};
    }

    return firstDigit + skipZeros({token, firstDigit});
}

size_t NumberParser::getFloatingPointPosition() const noexcept {
    size_t index = 0;
    char currentSymbol = token[index];
    while(currentSymbol != '\0') {
        if(isFloatingPoint(currentSymbol)) {
            return index;
        }
        ++index;
        currentSymbol = token[index];
    }

    return index;
}

long long NumberParser::parseInteger(ConstString& string) noexcept {
    const bool isNegative = isMinus(string[0]);
    const size_t firstDigit = (isNegative || isPlus(string[0])) ? 1 : 0;
    size_t index = firstDigit + skipZeros({string, firstDigit});
    char currentSymbol = string[index];
    long long integer = 0;
    while(currentSymbol != '\0') {
        integer *= 10;
        integer += toDigit(currentSymbol);
        ++index;
        currentSymbol = string[index];
    }

    return isNegative ? (-integer) : integer;
}

double NumberParser::parseFloatingPart(const ConstString& string) noexcept {
    long long floatingPart = 0;
    unsigned long long floatingExponent = 1;
    size_t index = 0;
    char currentSymbol = string[index];
    while(currentSymbol != '\0') {
        if((floatingPart != 0) || (!isZero(currentSymbol))) {
            floatingPart *= 10;
            floatingPart += toDigit(currentSymbol);
        }
        floatingExponent *= 10;
        ++index;
        currentSymbol = string[index];
    }
    return static_cast<double>(floatingPart) / static_cast<double>(floatingExponent);
}

NumberParser::NumberParser(ConstString& string) noexcept
: TypeParser<Number>{string} {}

Number NumberParser::typeParser() const {
    const size_t floatingPointPosition = getFloatingPointPosition();
    const size_t tokenLength = token.length();
    if(floatingPointPosition == tokenLength) {
        return {parseInteger(token)};
    }
    const size_t positionAfterFloatingPoint = floatingPointPosition + 1;
    const size_t countOfZerosAfterFloatingPoint = skipZeros({token, positionAfterFloatingPoint});
    long long integerPart = parseInteger({token.cString(), floatingPointPosition});
    if((floatingPointPosition + countOfZerosAfterFloatingPoint + 1) == tokenLength) {
        return {integerPart};
    }
    double floatingPart = parseFloatingPart({token, positionAfterFloatingPoint});
    if(isMinus(token[0])) {
        floatingPart *= -1;
    }
    return {static_cast<double>(integerPart + floatingPart)};
}

size_t NumberParser::calculateFloatingPartLength(const size_t floatingPartBeginning) const {
    if(token[floatingPartBeginning] == '\0') {
        throw IncompleteDouble{};
    }
    const size_t countOfZerosAfterFloatingPoint = skipZeros({token, floatingPartBeginning});
    const size_t positionOfFirstNoneZeroDigitAfterFloatingPoint =
        floatingPartBeginning + countOfZerosAfterFloatingPoint;
    if(positionOfFirstNoneZeroDigitAfterFloatingPoint < token.length()) {
        return containsOnlyDigits(
            {token, positionOfFirstNoneZeroDigitAfterFloatingPoint},
            positionOfFirstNoneZeroDigitAfterFloatingPoint
        ) + countOfZerosAfterFloatingPoint;
    }
    return 0;
}

void NumberParser::typeValidator() const {
    const size_t firstNoneZeroDigitPosition = getFirstNoneZeroDigitPosition();
    if(firstNoneZeroDigitPosition == token.length()) {
        return;
    }
    ConstString tokenFromFirstDigit = {token, firstNoneZeroDigitPosition};
    size_t integerPartLength = 0;
    size_t floatingPartLength = 0;
    try {
        integerPartLength = containsOnlyDigits(tokenFromFirstDigit, firstNoneZeroDigitPosition);
    } catch(const InvalidSymbol& error) {
        const size_t invalidPosition = error.getPosition();
        integerPartLength = invalidPosition - firstNoneZeroDigitPosition;
        if(!isFloatingPoint(error.getSymbol())) {
            throw error;
        }
        floatingPartLength = calculateFloatingPartLength(invalidPosition + 1);
    }
    if((integerPartLength + floatingPartLength) > MAXIMUM_OF_DIGITS_COUNT) {
        throw NumberIsTooLong{};
    }
}