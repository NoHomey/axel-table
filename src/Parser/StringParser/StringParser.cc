#include "StringParser.h"
#include "../ValidationException/ValidationException.h"
#include "../DoubleParser/DoubleParser.h"

bool StringParser::isBackslash(const char symbol) noexcept {
    return symbol == '\\';
}

bool StringParser::isQuotes(const char symbol) noexcept {
    return symbol == '"';
}

StringParser::StringParser(ConstString& string) noexcept
: TypeParser<FixedSizeString>{string} {}

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

FixedSizeString StringParser::typeParser() const {
    ConstString tokenWithoutQuotes = {token, isQuotes(token[0]), isQuotes(token[token.length() - 1])};
    DoubleParser doubleParser = {tokenWithoutQuotes};
    try {
        doubleParser.validateType();
    } catch(const parse_exception::InvalidSymbol&) {
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
    throw parse_exception::ParsedAsDouble{doubleParser.parseType()};
}

bool StringParser::isCountOfBackslashesOdd(const size_t from, const size_t to) noexcept {
    return (to - from) % 2;
}

void StringParser::validateBackslashesBefore(const size_t lastChecked) const {
    size_t position;
    bool isBackslashesCountOdd;
    for(size_t index = isQuotes(token[0]); index <= lastChecked; ++index) {
        if(isQuotes(token[index])) {
            throw parse_exception::NotEscapedQuotes{index};
        }
        if(isBackslash(token[index])) {
            position = index;
            do {
                ++index;
            } while(isBackslash(token[index]));
            isBackslashesCountOdd = isCountOfBackslashesOdd(position, index);
            if(isQuotes(token[index])) {
                if(!isBackslashesCountOdd) {
                    throw parse_exception::NotEscapedQuotes{index};
                }
            } else if(isBackslashesCountOdd) {
                throw parse_exception::AloneBackslash{index - 1};
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
        throw parse_exception::MissingQuotesInTheEnd{};
    }
    validateBackslashesBefore(index);
}

void StringParser::typeValidator() const {
    const bool startsWithQuotes = isQuotes(token[0]);
    const size_t length = token.length();
    const bool endsWithQuotes = isQuotes(token[length - 1]);
    if(startsWithQuotes ^ endsWithQuotes) {
        if(startsWithQuotes) {
            throw parse_exception::MissingQuotesInTheEnd{};
        }
        if(endsWithQuotes) {
            throw parse_exception::MissingQuotesInTheBeginng{};
        }
    }
    if(endsWithQuotes && (length == 2)) {
        throw parse_exception::EmptyString{};
    }
    try {
        ConstString tokenWithoutQuotes = {token, startsWithQuotes, endsWithQuotes};
        DoubleParser{tokenWithoutQuotes}.validateType();
    } catch(const parse_exception::InvalidSymbol& error) {
        if(!startsWithQuotes) {
            throw parse_exception::MissingQuotes{};
        }
        validateBackslashes(length);
    }
}