#include "TypeParser.h"
#include "../ValidationException/ValidationException.h"

template<typename Type>
TypeParser<Type>::TypeParser(ConstString& string) noexcept
: token{string} {}

template<typename Type>
Type TypeParser<Type>::parseType() {
    if(token.isEmpty()) {
        throw parse_exception::Empty{};
    }
    if(token.isNull()) {
        throw parse_exception::Null{};
    }
    typeValidator();

    return typeParser();
}

template class TypeParser<long long>;
template class TypeParser<double>;
//template class TypeParser<ConstString>;