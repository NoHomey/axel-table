#include "StringObjectIterator.h"

StringObjectIterator::StringObjectIterator(const StringObject& string) noexcept
: iterated{string}, position{string.cString()} {
}

void StringObjectIterator::next() noexcept {
    if(iterated.isNull()) {
        return;
    }
    if(*position != '\0') {
        ++position;
    }
}

bool StringObjectIterator::isEndReached() const noexcept {
    return iterated.isNull() || (*position == '\0');
}

bool StringObjectIterator::isMoved() const noexcept {
    return position != iterated.cString();
}

const StringObject& StringObjectIterator::getIterated() const noexcept {
    return iterated;
}

const char* StringObjectIterator::getPosition() const noexcept {
    return position;
}