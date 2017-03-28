#include "StringObject.h"

StringObject::StringObject() noexcept
: string{nullptr} {}

StringObject::~StringObject() noexcept { }

StringObject::StringObject(const StringObject& other) noexcept
: string{other.string} {}

StringObject::StringObject(const char* cstring) noexcept
: string{const_cast<char*>(cstring)} {}

bool StringObject::isNull() const noexcept {
    return string == nullptr;
}

bool StringObject::isEmpty() const noexcept {
    if(isNull()) {
        return false;
    }

    return string[0] == '\0';
}

bool StringObject::hasContent() const noexcept {
    return !(isNull() || isEmpty());
}

size_t StringObject::length() const noexcept {
    if(isNull()) {
        return 0;
    }
    size_t size = 0;
    while(string[size] != '\0') {
        ++size;
    }

    return size;
}

const char* StringObject::cString() const noexcept {
    return string;
}

char StringObject::operator[](const size_t index) const noexcept {
    if(isNull()) {
        return '\0';
    }

    return index < length() ? string[index] : '\0';
}

bool StringObject::operator==(const StringObject& other) const noexcept {
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
        if(string[index] != other.string[index]) {
            return false;
        } else if(string[index] == '\0') {
            return true;
        }
        ++index;
    }
}

bool StringObject::operator!=(const StringObject& other) const noexcept {
    return !(*this == other);
}

bool StringObject::operator<(const StringObject& other) const noexcept {
    const bool thisContent = hasContent();
    const bool otherContent = other.hasContent();
    if(thisContent != otherContent) {
        return (!thisContent) && otherContent;
    } else if(!thisContent) {
        return false;
    }
    size_t index = 0;
    while(true) {
        if(string[index] != other.string[index]) {
            return string[index] < other.string[index];
        } else if(string[index] == '\0') {
            return false;
        }
        ++index;
    }
}