#include "Number.h"
#include <cmath>
#include <cfenv>

#define COMMON_ASSIGN_OPERATOR(opt)                     \
if(isInteger() && number.isInteger()) {                 \
    numberValue.integerValue opt number.getInteger();   \
} else {                                                \
    if(isInteger()) {                                   \
        numberValue.realValue = getInteger();           \
        numberType = NumberType::Real;                  \
    }                                                   \
    numberValue.realValue opt number.getValue();        \
}                                                       \
return *this

#define COMMON_VALUE_OPERATOR(opt)     \
Number result = *this;                 \
result opt number;                     \
return result

Number::Number(const long long integer) noexcept
: numberType{NumberType::Integer}, numberValue{integer} {}

Number::Number(const double real) noexcept
: numberType{NumberType::Real}, numberValue{0} {
    numberValue.realValue = real;
}

bool Number::isInteger() const noexcept {
    return numberType == NumberType::Integer;
}

bool Number::isReal() const noexcept {
    return numberType == NumberType::Real;
}

long long Number::getInteger() const noexcept {
    return numberValue.integerValue;
}

double Number::getReal() const noexcept {
    return numberValue.realValue;
}

double Number::Number::getValue() const noexcept {
    return isReal() ? getReal() : getInteger();
}

Number& Number::operator+=(const Number& number) noexcept {
    COMMON_ASSIGN_OPERATOR(+=);
}

Number Number::operator+(const Number& number) const noexcept {
    COMMON_VALUE_OPERATOR(+=);
}

Number& Number::operator-=(const Number& number) noexcept {
    if(number.isInteger()) {
        return *this += -number.getInteger();
    }
    return *this += -number.getReal();
}

Number Number::operator-(const Number& number) const noexcept {
    COMMON_VALUE_OPERATOR(-=);
}

Number& Number::operator*=(const Number& number) noexcept {
    COMMON_ASSIGN_OPERATOR(*=);
}

Number Number::operator*(const Number& number) const noexcept {
    COMMON_VALUE_OPERATOR(*=);
}

Number& Number::operator/=(const Number& number) {
    if(number.isInteger() && (0 == number.getInteger())) {
        throw DivisionByZero{};
    }
    const double nominator = getValue();
    const double denominator = number.getValue();
    numberValue.realValue = nominator / denominator;
    numberType = NumberType::Real;
    return *this;
}

Number  Number::operator/(const Number& number) const {
    COMMON_VALUE_OPERATOR(/=);
}

template<typename BaseType>
BaseType Number::positiveIntegerExponent(const BaseType base, const long long exponent) noexcept {
    if(exponent == 1) {
        return base;
    }
    if(exponent == 2) {
        return base * base;
    }
    BaseType result = 1;
    BaseType currentBase = base;
    long long currentExponent = exponent;
    while(currentExponent) {
        if(currentExponent & 1) {
            result *= currentBase;
        }
        currentExponent >>= 1;
        currentBase *= currentBase;
    }

    return result;
}

double Number::realOnIntegerExponent(const double base, const long long exponent) noexcept { 
    if(exponent < 0) {
        return 1.0 / positiveIntegerExponent(base, -exponent);
    }
    return positiveIntegerExponent(base, exponent);
}

bool Number::isPowerOfTwo(const long long base) noexcept {
    return ((base != 0) && !(base & (base - 1)));
}

unsigned int Number::whichPowerOfTwo(const long long base) noexcept {
    unsigned int powerOfTwo = 1;
    long long twoOnCurrentPower = 2;
    while(twoOnCurrentPower != 0) {
        if((base | twoOnCurrentPower) == base) {
            break;
        }
        ++powerOfTwo;
        twoOnCurrentPower <<= 1;
    }
    return powerOfTwo;
}

long long Number::integerOnPositiveIntegerExponent(const long long base, const long long exponent) noexcept {
    if(base < 0) {
        return ((exponent & 1) ? (-1) : 1) * integerOnPositiveIntegerExponent(-base, exponent);
    }
    if(isPowerOfTwo(base)) {
        return 2 << ((whichPowerOfTwo(base) * exponent) - 1);
    }
    return positiveIntegerExponent(base, exponent);
}

Number& Number::integerOnIntegerExponent(const long long exponent) {
    const long long thisValue = getInteger();
    if(thisValue == 1) {
        return *this;
    }
    if(thisValue == -1) {
        if((exponent % 2) == 0) {
            numberValue.integerValue = 1;
        }
        return *this;
    }
    const bool isThisValueZero = thisValue == 0;
    if(exponent < 0) {
        if(isThisValueZero) {
            throw DivisionByZero{};
        }
        const long long onPositiveExponent = integerOnPositiveIntegerExponent(thisValue, -exponent);
        numberValue.realValue = 1.0 / static_cast<double>(onPositiveExponent);
        numberType = NumberType::Real;
    } else {
        numberValue.integerValue = isThisValueZero ? 0 :
                                            integerOnPositiveIntegerExponent(thisValue, exponent);
    }
    return *this;
}

bool Number::isRealZero() const noexcept {
    return (FP_ZERO == std::fpclassify(getValue()));
}

Number& Number::operator^=(const Number& number) {
    if(number.isInteger()) {
        const long long exponent = number.getInteger();
        const bool isTypeInteger = isInteger();
        if(exponent == 0) {
            if(isTypeInteger && (0 == getInteger())) {
                throw ZeroRaisedOnZero{};
            }
            numberValue.integerValue = 1;
            numberType = NumberType::Integer;
            return *this;
        }
        if(isTypeInteger) {
            return integerOnIntegerExponent(exponent);
        }
        numberValue.realValue = realOnIntegerExponent(getReal(), exponent);
    } else {
        if(isRealZero() && number.isRealZero()) {
            throw ZeroRaisedOnZero{};
        }
        std::feclearexcept(FE_ALL_EXCEPT);
        numberValue.realValue = std::pow(getValue(), number.getReal());
        numberType = NumberType::Real;
        if(std::fetestexcept(FE_DIVBYZERO)) {
            throw DivisionByZero{};
        }
        if(std::fetestexcept(FE_INVALID)) {
            throw NegativeNumberRaisedOnNoneIntegerPower{};
        }
        /*if(std::fetestexcept(FE_INEXACT)) {
            // rounding
        }*/
    }

    return *this;
}

Number Number::operator^(const Number& number) const {
    COMMON_VALUE_OPERATOR(^=);
}

#undef COMMON_ASSIGN_OPERATOR

#undef COMMON_VALUE_OPERATOR