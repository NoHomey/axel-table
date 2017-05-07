#pragma once

#include "../Exception.h"

class Number {
public: 
    class DivisionByZero: public Exception { };

    class ZeroRaisedOnZero: public Exception { };

    class NegativeNumberRaisedOnNoneIntegerPower: public Exception { }; 

    Number(const long long integer = 0) noexcept;

    Number(const double real) noexcept;

    Number operator-() const noexcept;

    Number& operator+=(const Number& number) noexcept;
    Number operator+(const Number& number) const noexcept;

    Number& operator-=(const Number& number) noexcept;
    Number operator-(const Number& number) const noexcept;

    Number& operator*=(const Number& number) noexcept;
    Number operator*(const Number& number) const noexcept;

    Number& operator/=(const Number& number);
    Number operator/(const Number& number) const;

    Number& operator^=(const Number& number);
    Number operator^(const Number& number) const;

protected:
    enum NumberType {
        Integer,
        Real
    };

    union NumberValue {
        long long integerValue;
        double realValue;
    };

    bool isInteger() const noexcept;

    bool isReal() const noexcept;

    long long getInteger() const noexcept;

    double getReal() const noexcept;

    double getValue() const noexcept;

private:
    template<typename BaseType>
    static BaseType positiveIntegerExponent(const BaseType base, const long long exponent) noexcept; 

    static double realOnIntegerExponent(const double base, const long long exponent) noexcept;

    static bool isRealZero(const double number) noexcept;

    Number& integerOnIntegerExponent(const long long exponent);

    bool isZero() const noexcept;

    Number& integerExponent(const long long exponent);

    Number& realExponent(const double exponent);

    static const double EPSILON; 

protected:
    NumberType numberType;
    NumberValue numberValue;
};