#pragma once

#include "../BasicString/BasicString.h"

class FixedSizeString: public BasicString<char*> {
public:
    explicit FixedSizeString(const size_t chars);

    ~FixedSizeString() noexcept;

    FixedSizeString(const FixedSizeString&) = delete;

    FixedSizeString(FixedSizeString&& other) noexcept;

    FixedSizeString(const FixedSizeString&& other) = delete;

    FixedSizeString& operator=(const FixedSizeString&) = delete;

    FixedSizeString& operator=(FixedSizeString&& other) noexcept;

    FixedSizeString& operator<<(const char symbol) noexcept;

    bool isFilled() const noexcept;

protected:
    bool isntFilled() const noexcept;

    size_t filled;

private:
};