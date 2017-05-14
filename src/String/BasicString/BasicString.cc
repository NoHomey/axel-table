#include "BasicString.h"                                          

template<typename CString>
bool BasicString<CString>::shouldBeNull(const char* cstring, const size_t cstrLength) noexcept {
    return (cstring == nullptr) || (cstrLength == 0);
}

template<typename CString>
bool BasicString<CString>::constFalse(const char, const char) noexcept {
    return false;
}

template<typename CString>
bool BasicString<CString>::lessThanOperator(const char a, const char b) noexcept {
    return a < b;
}

template<typename CString>
BasicString<CString>::BasicString(CString cstring, const size_t cstrLength) noexcept
: ImmutableString{},
string{shouldBeNull(cstring, cstrLength) ? nullptr : cstring},
stringLength{string == nullptr ? 0 : cstrLength} { }

template<typename CString>
BasicString<CString>::~BasicString() noexcept { }

template<typename CString>
bool BasicString<CString>::isEmpty() const noexcept {
    return string == nullptr;
}

template<typename CString>
size_t BasicString<CString>::length() const noexcept {
    return stringLength;
}

template<typename CString>
const char* BasicString<CString>::cString() const noexcept {
    return string;
}

template<typename CString>
char BasicString<CString>::operator[](const size_t index) const noexcept {
    return index < stringLength ? string[index] : '\0';
}

template<typename CString>
bool  BasicString<CString>::compareStrings(const ImmutableString& other, const bool onEqual,
                        bool (*onDiff)(const char a, const char b)) const noexcept {
    if(this == &other) {
        return onEqual;
    }
    size_t index = 0;
    char thisChar;
    char otherChar;
    while(true) {
        thisChar = operator[](index);
        otherChar = other[index];
        if(thisChar != otherChar) {    
            return onDiff(thisChar, otherChar);
        } else if(thisChar == '\0') {
            return onEqual;
        }
        ++index;
    }
}

template<typename CString>
bool BasicString<CString>::operator==(const ImmutableString& other) const noexcept {
    return compareStrings(other, true, constFalse);
}

template<typename CString>
bool BasicString<CString>::operator!=(const ImmutableString& other) const noexcept {
    return !(*this == other);
}

template<typename CString>
bool BasicString<CString>::operator<(const ImmutableString& other) const noexcept {
    return compareStrings(other, false, lessThanOperator);
}

template<typename CString>
bool BasicString<CString>::operator>(const ImmutableString& other) const noexcept {
    return other < *this;
}

template class BasicString<char*>;
template class BasicString<const char*>;