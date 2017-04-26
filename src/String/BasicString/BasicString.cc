#include "BasicString.h"

template<typename CString>
BasicString<CString>::BasicString() noexcept
: ImmutableString{}, string{nullptr} {}

template<typename CString>
BasicString<CString>::~BasicString() noexcept { }

template<typename CString>
BasicString<CString>::BasicString(CString cstring) noexcept
: ImmutableString{}, string{cstring} {}

template<typename CString>
bool BasicString<CString>::isNull() const noexcept {
    return string == nullptr;
}

template<typename CString>
bool BasicString<CString>::isEmpty() const noexcept {
    if(isNull()) {
        return false;
    }

    return string[0] == '\0';
}

template<typename CString>
bool BasicString<CString>::hasContent() const noexcept {
    return !(isNull() || isEmpty());
}

template<typename CString>
size_t BasicString<CString>::length() const noexcept {
    if(isNull()) {
        return 0;
    }
    size_t size = 0;
    while(string[size] != '\0') {
        ++size;
    }

    return size;
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

    return index < length() ? string[index] : '\0';
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
    const char* otherString = other.cString();
    while(true) {
        if(string[index] != otherString[index]) {
            return false;
        } else if(string[index] == '\0') {
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
    const char* otherString = other.cString();
    while(true) {
        if(string[index] != otherString[index]) {
            return string[index] < otherString[index];
        } else if(string[index] == '\0') {
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