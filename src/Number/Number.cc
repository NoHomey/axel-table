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

const double Number::EPSILON = 1e-15;

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

bool Number::isRealZero(const double number) noexcept {
    if(number < 0) {
        return isRealZero(-number);
    }

    return number < EPSILON;
}

bool Number::isZero() const noexcept {
    if(isInteger()) {
        return getInteger() == 0;
    }

    return isRealZero(getReal());
}

Number Number::operator-() const noexcept {
    if(isInteger()) {
        return Number(-getInteger());
    }
    return Number(-getReal());
}

Number& Number::operator+=(const Number& number) noexcept {
    COMMON_ASSIGN_OPERATOR(+=);
}

Number Number::operator+(const Number& number) const noexcept {
    COMMON_VALUE_OPERATOR(+=);
}

Number& Number::operator-=(const Number& number) noexcept {
    return *this += -number;
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
    if(number.isZero()) {
        throw DivisionByZero{};
    }
    if(!isZero()) {
        const double nominator = getValue();
        const double denominator = number.getValue();
        numberValue.realValue = nominator / denominator;
        numberType = NumberType::Real;
    }
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
    if((thisValue == 1) || (thisValue == 0)) {
        return *this;
    }
    if(thisValue == -1) {
        if((exponent % 2) == 0) {
            numberValue.integerValue = 1;
        }
        return *this;
    }
    if(exponent < 0) {
        const long long thisValueOnPositiveExponent = integerOnPositiveIntegerExponent(thisValue, -exponent);
        numberValue.realValue = 1.0 / static_cast<double>(thisValueOnPositiveExponent);
        numberType = NumberType::Real;
    } else {
        numberValue.integerValue = integerOnPositiveIntegerExponent(thisValue, exponent);
    }
    return *this;
}

Number& Number::integerExponent(const long long exponent) {
    if(isZero() && (exponent < 0)) {
        throw DivisionByZero{};
    }
    if(isInteger()) {
        return integerOnIntegerExponent(exponent);
    }
    numberValue.realValue = realOnIntegerExponent(getReal(), exponent);
    return *this;
}

Number& Number::realExponent(const double exponent) {
    std::feclearexcept(FE_ALL_EXCEPT);
    numberValue.realValue = std::pow(getValue(), exponent);
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
    return *this;
}

Number& Number::operator^=(const Number& number) {
    if(number.isZero()) {
        if(isZero()) {
            throw ZeroRaisedOnZero{};
        }
        numberValue.integerValue = 1;
        numberType = NumberType::Integer;
        return *this;
    }
    if(number.isInteger()) {
        return integerExponent(number.getInteger());
    }
    return realExponent(number.getReal());
}

Number Number::operator^(const Number& number) const {
    COMMON_VALUE_OPERATOR(^=);
}

#undef COMMON_ASSIGN_OPERATOR

#undef COMMON_VALUE_OPERATOR