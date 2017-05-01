#pragma once

#include "../BasicString/BasicString.h"

class FixedSizeString: public BasicString<char*> {
public:
    FixedSizeString() noexcept;

    FixedSizeString(const char* cstring);

    FixedSizeString(const FixedSizeString& other, const size_t offset, const bool fromEnd = false);

    explicit FixedSizeString(const size_t chars);

    ~FixedSizeString();

    FixedSizeString(const FixedSizeString&) = delete;

    FixedSizeString(FixedSizeString&& other) noexcept;

    FixedSizeString(const FixedSizeString&& other) = delete;

    FixedSizeString& operator=(const FixedSizeString&) = delete;

    FixedSizeString& operator=(FixedSizeString&& other) noexcept;

    FixedSizeString& operator<<(const char symbol) noexcept;

    FixedSizeString& operator<<(const char* symbols) noexcept;

protected:
    bool isntFilled() const noexcept;

    size_t filled;
};