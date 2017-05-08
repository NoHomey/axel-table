#include "NumberParser.h"
#include "../ValidationException/ValidationException.h"

NumberParser::NumberParser(ConstString& string) noexcept
: TypeParser<Number>{string} {}

Number NumberParser::typeParser() const {
    return {};
}

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
    while(string[index] != '\0') {
        if(!isDigit(string[index])) {
            throw parse_exception::InvalidSymbol{index + offset, string[index]};
        }
        ++index;
    }

    return index;
}

size_t NumberParser::getFirstNoneZeroDigitPosition() const {
    const size_t firstDigit = NumberParser::isPlusMinus(token[0]) ? 1 : 0;
    if(token[firstDigit + 1] == '\0') {
        if(isFloatingPoint(token[firstDigit])) {
            throw parse_exception::SingleFloatingPoint{};
        }
        if(firstDigit == 1) {
            throw parse_exception::SingleSign{};
        }
    }
    if(isFloatingPoint(token[firstDigit])) {
        throw parse_exception::DoubleHasNoIntegerPart{};
    }

    return firstDigit + skipZeros({token, firstDigit});
}

void NumberParser::typeValidator() const {
    const size_t firstNoneZeroPosition = getFirstNoneZeroDigitPosition();
    if(firstNoneZeroPosition == token.length()) {
        return;
    }
    ConstString tokenFromFirstDigit = {token, firstNoneZeroPosition};
    size_t length;
    try {
        length = containsOnlyDigits(tokenFromFirstDigit, firstNoneZeroPosition);
    } catch(const parse_exception::InvalidSymbol& error) {
        if(!isFloatingPoint(error.getSymbol())) {
            throw error;
        }
        const size_t positionAfterFloatingPoint = error.getPosition() + 1;
        if(token[positionAfterFloatingPoint] == '\0') {
            throw parse_exception::IncompleteDouble{};
        }
    }
}