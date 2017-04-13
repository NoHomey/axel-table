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

    class InValid: public ValidationException {
    public:
        InValid(const size_t pos, const char sym) noexcept;

        InValid(const InValid&) = delete;

        InValid& operator=(const InValid&) = delete;
    };

    class Warnning: public ValidationException {
    public:
        Warnning(const size_t pos, const char sym) noexcept;

        Warnning(const Warnning&) = delete;

        Warnning& operator=(const Warnning&) = delete;
    };
}