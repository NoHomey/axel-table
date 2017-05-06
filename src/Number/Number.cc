#include "Number.h"

#define COMMON_ASSIGN_OPERATOR(opt)                                                      \
if(isInteger() && number.isInteger()) {                                                  \
    numberValue.integerValue opt number.getInteger();                                    \
} else {                                                                                 \
    if(isInteger()) {                                                                    \
        numberValue.realValue = getInteger();                                            \
        numberType = NumberType::Real;                                                   \
    }                                                                                    \
    numberValue.realValue opt number.isReal() ? number.getReal() : number.getInteger();  \
}                                                                                        \
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

Number& Number::operator+=(const Number& number) noexcept {
    COMMON_ASSIGN_OPERATOR(+=);
}

Number Number::operator+(const Number& number) const noexcept {
    COMMON_VALUE_OPERATOR(+=);
}

Number&  Number::operator-=(const Number& number) noexcept {
    if(number.isInteger()) {
        return *this += -number.getInteger();
    }
    return *this += -number.getReal();
}

Number  Number::operator-(const Number& number) const noexcept {
    COMMON_VALUE_OPERATOR(-=);
}

Number&  Number::operator*=(const Number& number) noexcept {
    COMMON_ASSIGN_OPERATOR(*=);
}

Number  Number::operator*(const Number& number) const noexcept {
    COMMON_VALUE_OPERATOR(*=);
}

/*Number&  Number::operator/=(const Number& number) noexcept;
Number  Number::operator/(const Number& number) const noexcept;

Number&  Number::operator^=(const Number& number) noexcept;
Number  Number::operator^(const Number& number) const noexcept;*/

#undef COMMON_ASSIGN_OPERATOR

#undef COMMON_VALUE_OPERATOR