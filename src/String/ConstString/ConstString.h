#pragma once

#include "../BasicString/BasicString.h"
#include "../../Exception.h"

class ConstCharString: public BasicString<const char*> {
public:
    class BadStringOffset: public Exception { };

    ConstCharString() noexcept = delete;

    ~ConstCharString() noexcept = default;

    ConstCharString(const ConstCharString&) noexcept = delete;

    ConstCharString(ConstCharString&&) = delete;

    ConstCharString& operator=(const ConstCharString&) = delete;

    ConstCharString& operator=(ConstCharString&&) = delete;

    ConstCharString(const char* cstring, const size_t cstrLength) noexcept;

    ConstCharString(const ConstCharString& other, const size_t offsetFromBegging);

    ConstCharString(const ConstCharString& other, const size_t offsetFromBegging, const size_t newLength);

private:
    static const char* currentString(const ConstCharString& other,const size_t offsetFromBegging,
                                                                    const bool extraCondition) noexcept;

    ConstCharString(const ConstCharString& other, const size_t offsetFromBegging,
                                                    const bool extraCondition, const size_t newLength);
};

using ConstString = const ConstCharString;