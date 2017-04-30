#pragma once

#include "../BasicString/BasicString.h"

class FixedSizeString: public BasicString<char*> {
public:
    explicit FixedSizeString(const size_t chars);

    ~FixedSizeString();

    FixedSizeString(const FixedSizeString&) = delete;

    FixedSizeString(FixedSizeString&&) = delete;

    FixedSizeString& operator=(const FixedSizeString&) = delete;

    FixedSizeString& operator=(FixedSizeString&& other) = delete;

    FixedSizeString& operator<<(const char symbol) noexcept;

    FixedSizeString& operator<<(const char* symbols) noexcept;

protected:
    bool isntFilled() const noexcept;

    size_t filled;
};