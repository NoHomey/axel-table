#include "TypeParser.h"

template<typename Type>
TypeParser<Type>::TypeParser(const StringObject& string) noexcept
: token{string}, validated{false} {}

template<typename Type>
void TypeParser<Type>::validate() {
    validated = true;
    validator();
}

template<typename Type>
bool TypeParser<Type>::isValidated() const noexcept {
    return validated;
}

template<typename Type>
Type TypeParser<Type>::parse() {
    if(!isValidated()) {
        validate();
    }

    return parser();
}

template class TypeParser<int>;
//template class TypeParser<double>;
//template class TypeParser<StringObject>;