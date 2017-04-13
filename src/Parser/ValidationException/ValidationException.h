#pragma once

#include <cstddef>
#include "../../Exception.h"

namespace parse_exception {
    class ValidationException: public Exception {
    public:
        ValidationException(const size_t pos, const char sym) noexcept;

        size_t getPosition() const noexcept;

        char getSymbol() const noexcept;

    protected:
        const size_t position;
        const char symbol;
    };

    class Invalid: public ValidationException {
    public:
        Invalid(const size_t pos, const char sym) noexcept;
    };

    class Empty: public Invalid {
    public:
        Empty() noexcept;
    };

    class Null: public Invalid {
    public:
        Null() noexcept;
    };

    class InvalidSymbol: public Invalid {
    public:
        InvalidSymbol(const size_t pos, const char sym) noexcept;
    };

    class SingleSign: public Invalid {
    public:
        SingleSign(const char sym) noexcept;
    };

    class Warning: public ValidationException {
    public:
        Warning(const size_t pos, const char sym) noexcept;
    };

    class Limit: public Warning {
    public:
        Limit(const size_t pos, const char sym) noexcept;
    };

    class LeadingZero: public Warning {
    public:
        LeadingZero(const size_t pos) noexcept;
    };
}