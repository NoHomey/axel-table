#include "ConstString.h"

const char* ConstCharString::currentString(ConstString& other, const size_t offsetFromBegging,
                                            const bool extraCondition) noexcept {
    return ((other.stringLength > 0) && extraCondition)
            ? (other.string + offsetFromBegging) : nullptr;
}

ConstCharString::ConstCharString(const char* cstring, const size_t cstrLength) noexcept
: BasicString{cstring, cstrLength} {}

ConstCharString::ConstCharString(ConstString& other, const size_t offsetFromBegging,
                                    const bool extraCondition, const size_t newLength)
: BasicString{currentString(other, offsetFromBegging, extraCondition), newLength} {
    if(string == nullptr) {
        throw BadStringOffset{};
    }
}

ConstCharString::ConstCharString(ConstString& other, const size_t offsetFromBegging)
: ConstCharString{
    other,
    offsetFromBegging,
    offsetFromBegging < other.stringLength,
    other.stringLength - offsetFromBegging
} { }

ConstCharString::ConstCharString(ConstString& other, const size_t offsetFromBegging,
                                                            const size_t newLength)
: ConstCharString{
    other,
    offsetFromBegging,
    (offsetFromBegging + newLength) <= other.stringLength,
    newLength
} { }