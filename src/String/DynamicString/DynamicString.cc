#include "DynamicString.h"
#include "../ConstString/ConstString.h"

size_t DynamicString::stringLength(const char* string) noexcept {
    size_t length = 0;
    if(string != nullptr) {
        char symbol = string[length];
        while(symbol != '\0') {
            ++length;
            symbol = string[length];
        }
    }
    return length;
}

size_t DynamicString::stringInitialLength(const char* string) noexcept {
    size_t length = stringLength(string);
    if(length > 0) {
        ++length;
    }
    return length;
}

DynamicString::DynamicString(const char* str)
: string{stringInitialLength(str)} {
    const size_t capacity = string.capacity();
    if(capacity > 0) {
        const size_t size = capacity - 1;
        for(size_t index = 0; index < size; ++index) {
            string.push(str[index]);
        }
        string.push('\0');
    }
}

bool DynamicString::isEmpty() const noexcept {
    return length() == 0;
}

size_t DynamicString::length() const noexcept {
    size_t size = string.size();
    if(size > 0) {
        --size;
    }
    return size;
}

size_t DynamicString::capacity() const noexcept {
    size_t capacity = string.capacity();
    if(capacity > 0) {
        --capacity;
    }
    return capacity;
}

const char* DynamicString::cString() const noexcept {
    return string.data();
}

char DynamicString::operator[](const size_t index) const noexcept {
    return !string.isEmpty() ? string[index] : '\0';
}

bool DynamicString::operator==(const ImmutableString& other) const noexcept {
    return (ConstString{cString(), length()}) == other;
}

bool DynamicString::operator!=(const ImmutableString& other) const noexcept {
    return !operator==(other);
}

bool DynamicString::operator<(const ImmutableString& other) const noexcept {
    return (ConstString{cString(), length()}) < other;
}

bool DynamicString::operator>(const ImmutableString& other) const noexcept {
    return other < *this;
}

void DynamicString::reserve(size_t size) {
    if(size > 0) {
        string.reserve(size + (string.capacity() == 0));
    }
}
    
void DynamicString::shrinkToFit() {
    string.shrinkToFit();
}

void DynamicString::clear() noexcept {
    string.clear();
}