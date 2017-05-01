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

FixedSizeString StringParser::typeParser() const {
    return nullptr;
}

bool StringParser::isCountOfBackslashesOdd(const size_t from, const size_t to) noexcept {
    return (to - from) % 2;
}

void StringParser::checkBetween(const size_t lastChecked) const {
    size_t position;
    bool isBackslashesCountOdd;
    for(size_t index = isQuotes(token[0]); index <= lastChecked; ++index) {
        if(isQuotes(token[index])) {
            throw parse_exception::NotEscapedQuotes{index};
        }
        if(isBackslash(token[index])) {
            position = index;
            ++index;
            while(isBackslash(token[index])) {
                ++index;
            }
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
    ConstString tokenWithoutLeadingQuotes = {token, static_cast<size_t>(startsWithQuotes)};
    ConstString tokenWihtoutEndingQuotes = {tokenWithoutLeadingQuotes, static_cast<size_t>(endsWithQuotes), true};
    DoubleParser doubleParser = {tokenWihtoutEndingQuotes};
    double doubleValue;
    try {
        doubleValue = doubleParser.parseType();
    } catch(const parse_exception::InvalidSymbol& error) {
        if(!startsWithQuotes) {
            throw parse_exception::MissingQuotes{};
        }
        size_t index = length - 2;
        while(isBackslash(token[index])) {
            --index;
        }
        if(isCountOfBackslashesOdd(index, length)) {
            throw parse_exception::MissingQuotesInTheEnd{};
        }
        checkBetween(index);
        return;
    }
    throw parse_exception::ParsedAsDouble{doubleValue};
}