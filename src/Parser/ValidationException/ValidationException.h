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

    class InvalidSymbol: public Invalid {
    public:
        InvalidSymbol(const size_t pos, const char sym) noexcept;

        size_t getPosition() const noexcept;

        char getSymbol() const noexcept;

    protected:
        const size_t position;
        const char symbol;
    };
}