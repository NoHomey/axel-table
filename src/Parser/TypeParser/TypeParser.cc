#include "TypeParser.h"
#include "../ValidationException/ValidationException.h"

template<typename Type>
TypeParser<Type>::TypeParser(ConstString& string) noexcept
: token{string}, validated{false} {}

template<typename Type>
void TypeParser<Type>::validate() {
    validated = true;
    if(token.isEmpty()) {
        throw parse_exception::Empty();
    }
    if(token.isNull()) {
        throw parse_exception::Null();
    }
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

template class TypeParser<long long>;
//template class TypeParser<double>;
//template class TypeParser<ConstString>;