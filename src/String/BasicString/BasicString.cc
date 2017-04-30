#include "BasicString.h"

template<typename CString>
size_t BasicString<CString>::calculateLength(CString cstring) noexcept {
    if(cstring == nullptr) {
        return 0;
    }
    size_t size = 0;
    while(cstring[size] != '\0') {
        ++size;
    }

    return size;
}

template<typename CString>
BasicString<CString>::BasicString(CString cstring, const size_t cstrLength) noexcept
: ImmutableString{}, string{cstring}, stringLength{cstrLength} {}

template<typename CString>
BasicString<CString>::BasicString() noexcept
: BasicString{nullptr} {}

template<typename CString>
BasicString<CString>::BasicString(CString cstring) noexcept
: BasicString{cstring, calculateLength(cstring)} {}

template<typename CString>
BasicString<CString>::BasicString(const BasicString& other, const size_t offset, const bool fromEnd)
: BasicString{fromEnd ? other.string : (other.string + offset), other.stringLength - offset} {
    if(offset > other.stringLength) {
        throw BadStringOffset{};
    }
}

template<typename CString>
BasicString<CString>::~BasicString() noexcept { }

template<typename CString>
bool BasicString<CString>::isNull() const noexcept {
    return string == nullptr;
}

template<typename CString>
bool BasicString<CString>::isEmpty() const noexcept {
    if(isNull()) {
        return false;
    }

    return stringLength == 0;
}

template<typename CString>
bool BasicString<CString>::hasContent() const noexcept {
    return !(isNull() || isEmpty());
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
    if(isNull()) {
        return '\0';
    }

    return index < stringLength ? string[index] : '\0';
}

template<typename CString>
bool BasicString<CString>::operator==(const ImmutableString& other) const noexcept {
    if(this == &other) {
        return true;
    }
    const bool thisContent = hasContent();
    if(thisContent == other.hasContent()) {
        if(!thisContent) {
            return true;
        }
    } else {
        return false;
    }
    size_t index = 0;
    while(true) {
        if(operator[](index) != other[index]) {
            return false;
        } else if(operator[](index) == '\0') {
            return true;
        }
        ++index;
    }
}

template<typename CString>
bool BasicString<CString>::operator!=(const ImmutableString& other) const noexcept {
    return !(*this == other);
}

template<typename CString>
bool BasicString<CString>::operator<(const ImmutableString& other) const noexcept {
    if(this == &other) {
        return false;
    }
    const bool thisContent = hasContent();
    const bool otherContent = other.hasContent();
    if(thisContent != otherContent) {
        return (!thisContent) && otherContent;
    } else if(!thisContent) {
        return false;
    }
    size_t index = 0;
    while(true) {
        if(operator[](index) != other[index]) {
            return operator[](index) < other[index];
        } else if(operator[](index) == '\0') {
            return false;
        }
        ++index;
    }
}

template<typename CString>
bool BasicString<CString>::operator>(const ImmutableString& other) const noexcept {
    return other < *this;
}

template class BasicString<char*>;
template class BasicString<const char*>;