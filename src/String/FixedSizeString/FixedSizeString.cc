#include "FixedSizeString.h"

FixedSizeString::FixedSizeString() noexcept
: BasicString<char*>{nullptr, 0}, filled{0} { }

FixedSizeString::FixedSizeString(const size_t chars)
: FixedSizeString{} {
    stringLength = chars;
    string = new char[chars + 1];
}

FixedSizeString::FixedSizeString(const char* cstring, const size_t chars)
: FixedSizeString{} {
    if(!shouldBeNull(cstring, chars)) {
        stringLength = chars;
        fill(cstring);
    }
}

FixedSizeString::FixedSizeString(const FixedSizeString& other, const size_t offsetFromBegging, const size_t offsetFromEnd)
: FixedSizeString{} {
    other.canBeParted(offsetFromBegging, offsetFromEnd);
    stringLength = other.stringLength - offsetFromBegging - offsetFromEnd;
    fill(other.string + offsetFromBegging);
}

FixedSizeString::FixedSizeString(FixedSizeString&& other) noexcept
: BasicString{other.string, other.stringLength}, filled{other.filled} {
    other.string = nullptr;
}

FixedSizeString::~FixedSizeString() {
    delete[] string;
    string = nullptr;
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

void FixedSizeString::fill(const char* cstring) noexcept {
    string = new char[stringLength];
    for(; filled < stringLength; ++filled) {
        string[filled] = cstring[filled];
    }
    string[filled] = '\0';
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