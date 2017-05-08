#include "StringParser.h"

bool StringParser::isBackslash(const char symbol) noexcept {
    return symbol == '\\';
}

bool StringParser::isQuotes(const char symbol) noexcept {
    return symbol == '"';
}

size_t StringParser::calculateParseResultStringLength() const noexcept {
    size_t index = 1;
    char currentSymbol = token[index];
    size_t calculatedLength = 0;
    while(true) {
        ++calculatedLength;
        index += isBackslash(currentSymbol) ? 2 : 1;
        currentSymbol = token[index];
        if(isQuotes(currentSymbol) && (token[index + 1] == '\0')) {
            return calculatedLength;
        }
    }
}

bool StringParser::isCountOfBackslashesOdd(const size_t from, const size_t to) noexcept {
    return (to - from) % 2;
}

void StringParser::validateBackslashesBefore(const size_t lastChecked) const {
    size_t position;
    bool isBackslashesCountOdd;
    for(size_t index = isQuotes(token[0]); index <= lastChecked; ++index) {
        if(isQuotes(token[index])) {
            throw NotEscapedQuotes{index};
        }
        if(isBackslash(token[index])) {
            position = index;
            do {
                ++index;
            } while(isBackslash(token[index]));
            isBackslashesCountOdd = isCountOfBackslashesOdd(position, index);
            if(isQuotes(token[index])) {
                if(!isBackslashesCountOdd) {
                    throw NotEscapedQuotes{index};
                }
            } else if(isBackslashesCountOdd) {
                throw AloneBackslash{index - 1};
            }
        }
    }
}

void StringParser::validateBackslashes(const size_t length) const {
    size_t index = length - 2;
    while(isBackslash(token[index])) {
        --index;
    }
    if(isCountOfBackslashesOdd(index, length)) {
        throw MissingQuotesInTheEnd{};
    }
    validateBackslashesBefore(index);
}

StringParser::StringParser(ConstString& string) noexcept
: TypeParser<FixedSizeString>{string} {}

StringParser::NotEscapedQuotes::NotEscapedQuotes(const size_t pos) noexcept
: InvalidSymbolAtPosition{pos} {}

StringParser::AloneBackslash::AloneBackslash(const size_t pos) noexcept
: InvalidSymbolAtPosition{pos} {}

FixedSizeString StringParser::typeParser() const {
    const size_t resultLength = calculateParseResultStringLength();
    FixedSizeString result{resultLength};
    size_t index = 1;
    char currentSymbol = token[index];
    for(size_t counter = 0; counter < resultLength; ++counter) {
        if(isBackslash(currentSymbol)) {
            ++index;
            currentSymbol = token[index];
        }
        result << currentSymbol;
        ++index;
        currentSymbol = token[index];
    }
    return result;
}

void StringParser::typeValidator() const {
    const bool startsWithQuotes = isQuotes(token[0]);
    const size_t length = token.length();
    const bool endsWithQuotes = isQuotes(token[length - 1]);
    if(startsWithQuotes ^ endsWithQuotes) {
        if(startsWithQuotes) {
            throw MissingQuotesInTheEnd{};
        }
        if(endsWithQuotes) {
            throw MissingQuotesInTheBeginng{};
        }
    }
    if(endsWithQuotes && (length == 2)) {
        throw EmptyString{};
    }
    if(!startsWithQuotes) {
        throw MissingQuotes{};
    }
    validateBackslashes(length);
}