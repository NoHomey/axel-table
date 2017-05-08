#pragma once

#include <cstddef>
#include "../../Exception.h"

class Invalid: public Exception { };

class Empty: public Invalid { };

class InvalidSymbolAtPosition: public Invalid {
public:
    InvalidSymbolAtPosition(const size_t pos) noexcept;

    size_t getPosition() const noexcept;

protected:
    const size_t position;
};

class InvalidSymbol: public InvalidSymbolAtPosition {
public:
    InvalidSymbol(const size_t pos, const char sym) noexcept;

    char getSymbol() const noexcept;

protected:
    const char symbol;
};