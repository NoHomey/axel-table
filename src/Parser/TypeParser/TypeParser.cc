#include "TypeParser.h"
#include "../ValidationException/ValidationException.h"
#include "../../String/FixedSizeString/FixedSizeString.h"

template<typename Type>
TypeParser<Type>::TypeParser(ConstString& string) noexcept
: token{string} {}

template<typename Type>
void TypeParser<Type>::validateType() const {
    if(!token.hasContent()) {
        throw parse_exception::Empty{};
    }
    typeValidator();
}

template<typename Type>
Type TypeParser<Type>::parseType() const {
    return typeParser();
}

template class TypeParser<long long>;
template class TypeParser<double>;
template class TypeParser<FixedSizeString>;