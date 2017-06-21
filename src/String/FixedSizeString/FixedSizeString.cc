#include "FixedSizeString.h"

FixedSizeString::FixedSizeString(const size_t chars)
: BasicString<char*>{new char[chars + 1], chars}, filled{0} { }

FixedSizeString::FixedSizeString(FixedSizeString&& other) noexcept
: BasicString{other.string, other.stringLength}, filled{other.filled} {
    other.string = nullptr;
}

FixedSizeString::~FixedSizeString() noexcept {
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

bool FixedSizeString::isntFilled() const noexcept {
    return filled < stringLength;
}

FixedSizeString& FixedSizeString::operator<<(const char symbol) noexcept {
    if(isntFilled()) {
        string[filled] = symbol;
        ++filled;
        if(isFilled()) {
            string[stringLength] = '\0';
        }
    }

    return *this;
}

bool FixedSizeString::isFilled() const noexcept {
    return filled == stringLength;
}