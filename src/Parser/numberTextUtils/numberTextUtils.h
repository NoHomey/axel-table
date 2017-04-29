#pragma once

#include <cstddef>

namespace numberTextUtils {
    bool isMinus(const char symbol) noexcept;

    bool isPlus(const char symbol) noexcept;

    bool isPlusMinus(const char symbol) noexcept;

    bool isZero(const char symbol) noexcept;

    bool isDigit(const char symbol) noexcept;
        
    unsigned int toDigit(const char symbol) noexcept;

    size_t skipZeros(const char* string) noexcept;

    size_t containsOnlyDigits(const char* string);
}