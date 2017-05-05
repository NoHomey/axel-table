#pragma once

#include "../BasicString/BasicString.h"

class FixedSizeString: public BasicString<char*> {
public:
    explicit FixedSizeString(const size_t chars);

    FixedSizeString(const char* cstring, const size_t chars);

    FixedSizeString(const FixedSizeString& other, const size_t offsetFromBegging, const size_t offsetFromEnd = 0);

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

private:
    FixedSizeString() noexcept;

    void fill(const char* cstring) noexcept;
};