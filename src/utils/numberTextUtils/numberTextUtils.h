#pragma once

namespace utils {
    namespace numberTextUtils {
        bool isMinus(const char symbol) noexcept;

        bool isPlus(const char symbol) noexcept;

        bool isPlusMinus(const char symbol) noexcept;

        bool isDigit(const char symbol) noexcept;

        bool matchesNumberBeginning(const char first, const char second) noexcept;
        
        unsigned int toDigit(const char symbol) noexcept;
    }
}