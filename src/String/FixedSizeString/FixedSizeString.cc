#include "FixedSizeString.h"

#include "../ConstString/ConstString.h"

FixedSizeString::FixedSizeString() noexcept
: BasicString<char*>{}, filled{0} { }

FixedSizeString::FixedSizeString(const char* cstring)
: FixedSizeString{} {
    stringLength = ConstString{cstring}.length();
    string = new char[stringLength + 1];
    for(size_t index = 0; index < stringLength; ++index) {
        string[index] = cstring[index];
    }
    filled = stringLength;
    string[filled] = '\0';
}

FixedSizeString::FixedSizeString(const FixedSizeString& other, const size_t offset, const bool fromEnd)
: FixedSizeString{} {
    if(offset > other.stringLength) {
        throw BadStringOffset{};
    }
    stringLength = other.stringLength - offset;
    string = new char[stringLength + 1];
    size_t index = offset;
    size_t copyLength = other.stringLength;
    if(fromEnd) {
        index = 0;
        copyLength = stringLength;
    }
    for(filled = 0; index < copyLength; ++index, ++filled) {
        string[filled] = other.string[index];
    }
    string[filled] = '\0';
}

FixedSizeString::FixedSizeString(const size_t chars)
: BasicString<char*>{new char[chars + 1], chars}, filled{0} { }

FixedSizeString::FixedSizeString(FixedSizeString&& other) noexcept
: BasicString{other.string, other.stringLength}, filled{other.filled} {
    other.string = nullptr;
}

FixedSizeString& FixedSizeString::operator=(FixedSizeString&& other) noexcept {
    if(this != &other) {
        delete[] string;
        string = other.string;
        other.string = nullptr;
        stringLength = other.stringLength;
        filled = other.filled;
    }
    return *this;
}

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