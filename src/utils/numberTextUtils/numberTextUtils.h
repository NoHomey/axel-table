#pragma once

namespace utils {
    namespace numberTextUtils {
        bool isMinus(const char symbol) noexcept;

        bool isPlus(const char symbol) noexcept;

        bool isPlusMinus(const char symbol) noexcept;

        bool isDigit(const char symbol) noexcept;

        bool matchesNumberFirstSymbol(const char symbol) noexcept;
        
        unsigned int toDigit(const char symbol) noexcept;
    }
}