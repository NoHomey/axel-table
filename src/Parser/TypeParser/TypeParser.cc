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

template class TypeParser<int>;