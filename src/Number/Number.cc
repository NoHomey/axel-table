#include "Number.h"
#include <cmath>
#include <cfenv>

#define COMMON_ASSIGN_OPERATOR(opt)                     \
if(isInteger() && number.isInteger()) {                 \
    numberValue.integerValue opt number.getInteger();   \
} else {                                                \
    if(isInteger()) {                                   \
        numberValue.realValue = getInteger();           \
        isValueInteger = false;                         \
    }                                                   \
    numberValue.realValue opt number.getValue();        \
}                                                       \
return *this

#define COMMON_VALUE_OPERATOR(opt)     \
Number result = *this;                 \
result opt number;                     \
return result

const double Number::EPSILON = 1e-15;

const Number Number::additionNeutralElement = {(const long long)0};

const Number Number::multiplicationNeutralElement = {(const long long)1};

Number::Number(const long long integer) noexcept
: isValueInteger{true}, numberValue{integer} {}

Number::Number(const double real) noexcept
: isValueInteger{false}, numberValue{0} {
    numberValue.realValue = real;
}

bool Number::isInteger() const noexcept {
    return isValueInteger;
}

bool Number::isReal() const noexcept {
    return !isInteger();
}

template<typename ReturnType>
ReturnType Number::getValueAs() const noexcept {
    return isInteger() ? numberValue.integerValue : numberValue.realValue;
}

long long Number::getInteger() const noexcept {
    return getValueAs<long long>();
}

double Number::getReal() const noexcept {
    return getValueAs<double>();
}

double Number::Number::getValue() const noexcept {
    return getReal();
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
        isValueInteger = false;
    }
    return *this;
}

Number  Number::operator/(const Number& number) const {
    COMMON_VALUE_OPERATOR(/=);
}

template<typename BaseType>
BaseType Number::positiveIntegerExponent(const BaseType base, const long long exponent) noexcept {
    BaseType result = 1;
    BaseType currentBase = base;
    long long currentExponent = exponent;
    while(true) {
        if(currentExponent & 1) {
            result *= currentBase;
            if(currentExponent == 1) {
                return result;
            }
        }
        currentExponent >>= 1;
        currentBase *= currentBase;
    }
}

double Number::realOnIntegerExponent(const double base, const long long exponent) noexcept { 
    if(exponent < 0) {
        return 1.0 / positiveIntegerExponent(base, -exponent);
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
        const long long thisValueOnPositiveExponent = positiveIntegerExponent(thisValue, -exponent);
        numberValue.realValue = 1.0 / static_cast<double>(thisValueOnPositiveExponent);
        isValueInteger = false;
    } else {
        numberValue.integerValue = positiveIntegerExponent(thisValue, exponent);
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
    isValueInteger = false;
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
        isValueInteger = true;
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

const Number& Number::getAdditionNeutralElement() noexcept {
    return additionNeutralElement;
}

const Number& Number::getMultiplicationNeutralElement() noexcept {
    return multiplicationNeutralElement;
}

#undef COMMON_ASSIGN_OPERATOR

#undef COMMON_VALUE_OPERATOR