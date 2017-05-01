#pragma once

#include <cstddef>
#include "../../Exception.h"

namespace parse_exception {
    class Invalid: public Exception { };

    class Empty: public Invalid { };

    class Null: public Invalid { };

    class SingleSign: public Invalid { };

    class Limit: public Invalid { };

    class MinimumLimit: public Limit { };

    class MaximumLimit: public Limit { };

    class LossOfPrecision: public Limit { };

    class MissingQuotesInTheBeginng: public Invalid { };

    class MissingQuotesInTheEnd: public Invalid { };

    class InvalidSymbolAtPosition: public Invalid {
    public:
        InvalidSymbolAtPosition(const size_t pos) noexcept;

        size_t getPosition() const noexcept;

    protected:
        const size_t position;
    };

    class NotEscapedQuotes: public InvalidSymbolAtPosition {
    public:
        NotEscapedQuotes(const size_t pos) noexcept;
    };

    class AloneBackslash: public InvalidSymbolAtPosition {
    public:
        AloneBackslash(const size_t pos) noexcept;
    };

    class InvalidSymbol: public InvalidSymbolAtPosition {
    public:
        InvalidSymbol(const size_t pos, const char sym) noexcept;

        char getSymbol() const noexcept;

    protected:
        const char symbol;
    };

    template<typename Type>
    class ParsedAsDifferentType: public Invalid {
    public:
        ParsedAsDifferentType(const Type val) noexcept;

        Type getValue() const noexcept;
        
    protected:
        Type value;
    };

    using ParsedAsInteger = ParsedAsDifferentType<long long>;

    using ParsedAsDouble = ParsedAsDifferentType<double>;
}