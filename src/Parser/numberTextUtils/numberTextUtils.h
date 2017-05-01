#pragma once

#include <cstddef>

#include "../../String/ConstString/ConstString.h"

#include "../ValidationException/ValidationException.h"

namespace numberTextUtils {
    bool isMinus(const char symbol) noexcept;

    bool isPlus(const char symbol) noexcept;

    bool isPlusMinus(const char symbol) noexcept;

    bool isZero(const char symbol) noexcept;

    bool isDigit(const char symbol) noexcept;
        
    unsigned int toDigit(const char symbol) noexcept;

    size_t skipZeros(ConstString& string) noexcept;

    size_t containsOnlyDigits(ConstString& string);

    void throwLimitException(const char symbol);
}