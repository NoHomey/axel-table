#pragma once

namespace utils {
    namespace textUtils {
        bool isMinus(const char symbol) noexcept;

        bool isPlus(const char symbol) noexcept;

        bool isDigit(const char symbol) noexcept;
        
        unsigned int toDigit(const char symbol) noexcept;
    }
}