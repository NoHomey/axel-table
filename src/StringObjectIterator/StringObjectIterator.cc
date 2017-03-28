#include "StringObjectIterator.h"

StringObjectIterator::StringObjectIterator(const StringObject& string) noexcept
: iterated{string}, position{string.cString()} {}

void StringObjectIterator::next() noexcept {
    
}

bool StringObjectIterator::isMoved() const noexcept {
    return false;
}

const StringObject& StringObjectIterator::getIterated() const noexcept {
    return iterated;
}

const char* StringObjectIterator::getPosition() const noexcept {
    return position;
}