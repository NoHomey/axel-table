#pragma once

#include <cstddef>
#include "../../Exception.h"

namespace parse_exception {
    class ValidationException: public Exception {
    public:
        ValidationException(const size_t pos, const char sym) noexcept;

        ValidationException(const ValidationException&) = delete;

        ValidationException& operator=(const ValidationException&) = delete;

        size_t getPosition() const noexcept;

        char getSymbol() const noexcept;

    protected:
        const size_t position;
        const char symbol;
    };

    class Invalid: public ValidationException {
    public:
        Invalid(const size_t pos, const char sym) noexcept;

        Invalid(const Invalid&) = delete;

        Invalid& operator=(const Invalid&) = delete;
    };

    class Warning: public ValidationException {
    public:
        Warning(const size_t pos, const char sym) noexcept;

        Warning(const Warning&) = delete;

        Warning& operator=(const Warning&) = delete;
    };
}