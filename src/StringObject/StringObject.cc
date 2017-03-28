#include "StringObject.h"

StringObject::StringObject() noexcept
: string{nullptr} {}

StringObject::~StringObject() noexcept { }

StringObject::StringObject(const StringObject& other) noexcept
: string{other.string} {}

StringObject::StringObject(const char* cstring) noexcept
: string{const_cast<char*>(cstring)} {}

size_t StringObject::length() const noexcept {
    if(string == nullptr) {
        return 0;
    }
    size_t size = 0;
    while(string[size] != '\0') {
        ++size;
    }

    return size;
}