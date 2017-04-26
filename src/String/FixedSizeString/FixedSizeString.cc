#include "FixedSizeString.h"

FixedSizeString::FixedSizeString(const size_t chars)
: BasicString<char*>{new char[chars]}, size{chars}, filled{0} {}

FixedSizeString::~FixedSizeString() {
    delete[] string;
    string = nullptr;
}

size_t FixedSizeString::length() const noexcept {
    return size;
}
