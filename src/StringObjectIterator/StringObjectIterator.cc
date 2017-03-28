#include "StringObjectIterator.h"

StringObjectIterator::StringObjectIterator(const StringObject& string) noexcept
: iterated{string}, position{string.cString()} {}

const StringObject& StringObjectIterator::getIterated() const noexcept {
    return iterated;
}

const char* StringObjectIterator::getPosition() const noexcept {
    return position;
}