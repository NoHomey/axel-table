#pragma once

#include "../TypeParser/TypeParser.h"
#include "../../Number/Number.h"

class NumberParser: public TypeParser<Number> {
public:
    NumberParser(ConstString& string) noexcept;

    NumberParser(const NumberParser&) = delete;

    NumberParser(NumberParser&&) = delete;

    NumberParser& operator=(const NumberParser&) = delete;

    NumberParser& operator=(NumberParser&&) = delete;
    
protected:
    void typeValidator() const override final;

    Number typeParser() const override final;

private:
    static bool isMinus(const char symbol) noexcept;

    static bool isPlus(const char symbol) noexcept;

    static bool isPlusMinus(const char symbol) noexcept;

    static bool isFloatingPoint(const char symbol) noexcept;

    static bool isZero(const char symbol) noexcept;

    static bool isDigit(const char symbol) noexcept;
        
    static unsigned int toDigit(const char symbol) noexcept;

    static size_t skipZeros(ConstString& string) noexcept;

    static size_t containsOnlyDigits(ConstString& string, const size_t offset);

    size_t getFirstNoneZeroDigitPosition() const;

    static const size_t MAXIMUM_OF_DIGITS_COUNT = 16;
};