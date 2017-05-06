#pragma once

class Number {
public: 
    Number(const long long integer) noexcept;

    Number(const double real) noexcept;

    Number& operator+=(const Number& number) noexcept;
    Number operator+(const Number& number) const noexcept;

    Number& operator-=(const Number& number) noexcept;
    Number operator-(const Number& number) const noexcept;

    Number& operator*=(const Number& number) noexcept;
    Number operator*(const Number& number) const noexcept;

    Number& operator/=(const Number& number) noexcept;
    Number operator/(const Number& number) const noexcept;

    Number& operator^=(const Number& number) noexcept;
    Number operator^(const Number& number) const noexcept;

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

    NumberType numberType;
    NumberValue numberValue;
};