#include "FixedSizeString.h"

FixedSizeString::FixedSizeString(const size_t chars)
: BasicString<char*>{new char[chars + 1], chars}, filled{0} {}

FixedSizeString::~FixedSizeString() {
    delete[] string;
    string = nullptr;
}

bool FixedSizeString::isntFilled() const noexcept {
    return filled < stringLength;
}

FixedSizeString& FixedSizeString::operator<<(const char symbol) noexcept {
    if(isntFilled()) {
        string[filled] = symbol;
        ++filled;
        if(filled == stringLength) {
            string[stringLength] = '\0';
        }
    }

    return *this;
}

FixedSizeString& FixedSizeString::operator<<(const char* symbols) noexcept {
    size_t i = 0;
    while(isntFilled() && (symbols[i] != '\0')) {
        operator<<(symbols[i]);
        ++i;
    }

    return *this;
}