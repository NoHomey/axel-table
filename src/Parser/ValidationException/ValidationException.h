#pragma once

#include <cstddef>
#include "../../Exception.h"

namespace parse_exception {
    class Invalid: public Exception { };

    class Empty: public Invalid { };

    class SingleSign: public Invalid { };

    class Limit: public Invalid { };

    class MinimumLimit: public Limit { };

    class MaximumLimit: public Limit { };

    class LossOfPrecision: public Limit { };

    class NumberIsTooLong: public Invalid { };

    class DoubleHasNoIntegerPart: public Invalid { };

    class SingleFloatingPoint: public Invalid { };

    class IncompleteDouble: public Invalid { };

    class MissingQuotes: public Invalid { };

    class MissingQuotesInTheBeginng: public MissingQuotes { };

    class MissingQuotesInTheEnd: public MissingQuotes { };

    class EmptyString: public Invalid { };

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
}