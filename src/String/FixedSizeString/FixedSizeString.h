#pragma once

#include "../BasicString/BasicString.h"

class FixedSizeString: public BasicString<char*> {
public:
    explicit FixedSizeString(const size_t chars);

    ~FixedSizeString();

    FixedSizeString(const FixedSizeString&) = delete;

    FixedSizeString& operator=(const FixedSizeString&) = delete;

    size_t length() const noexcept override final;

    FixedSizeString& operator<<(const char symbol) noexcept;

    FixedSizeString& operator<<(const char* symbols) noexcept;

protected:
    const size_t size;

    size_t filled;
};