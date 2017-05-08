#pragma once

#include "../TypeParser/TypeParser.h"
#include "../../Number/Number.h"
#include "../ValidationException/ValidationException.h"

class NumberParser: public TypeParser<Number> {
public:
    class SingleSign: public Invalid { };

    class NumberIsTooLong: public Invalid { };

    class DoubleHasNoIntegerPart: public Invalid { };

    class SingleFloatingPoint: public Invalid { };

    class IncompleteDouble: public Invalid { };

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

    static long long parseInteger(ConstString& string) noexcept;

    static double parseFloatingPart(const ConstString& string) noexcept;

    size_t getFirstNoneZeroDigitPosition() const;

    size_t calculateFloatingPartLength(const size_t floatingPartBeginning) const;

    size_t getFloatingPointPosition() const noexcept;

    static const size_t MAXIMUM_OF_DIGITS_COUNT = 16;
};