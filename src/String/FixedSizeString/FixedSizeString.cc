#include "FixedSizeString.h"

FixedSizeString::FixedSizeString(const size_t chars)
: BasicString<char*>{new char[chars + 1]}, size{chars}, filled{0} {}

FixedSizeString::~FixedSizeString() {
    delete[] string;
    string = nullptr;
}

size_t FixedSizeString::length() const noexcept {
    return size;
}

FixedSizeString& FixedSizeString::operator<<(const char symbol) noexcept {
    if(filled < size) {
        string[filled] = symbol;
        ++filled;
        if(filled == size) {
            string[size] = '\0';
        }
    }

    return *this;
}

FixedSizeString& FixedSizeString::operator<<(const char* symbols) noexcept {
    size_t i = 0;
    while((filled < size) && (symbols[i] != '\0')) {
        operator<<(symbols[i]);
        ++i;
    }

    return *this;
}