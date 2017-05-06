#pragma once

#include "Number.h"

class NumberHelper: public Number {
public:
    NumberHelper(const Number& number) noexcept;
    using Number::getInteger;
    using Number::getReal;
};