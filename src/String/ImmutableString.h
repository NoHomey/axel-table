#pragma once

#include <cstddef>

class ImmutableString {
public:
    ImmutableString() noexcept = default;

    virtual ~ImmutableString() noexcept = default;

    ImmutableString(const ImmutableString&) = default;

    ImmutableString(ImmutableString&&) = default;

    ImmutableString& operator=(const ImmutableString&) = default;

    ImmutableString& operator=(ImmutableString&&) = default;

    virtual bool isEmpty() const noexcept = 0;

    virtual size_t length() const noexcept = 0;

    virtual const char* cString() const noexcept = 0;

    virtual char operator[](const size_t index) const noexcept = 0;

    virtual bool operator==(const ImmutableString& other) const noexcept = 0;

    virtual bool operator!=(const ImmutableString& other) const noexcept = 0;

    virtual bool operator<(const ImmutableString& other) const noexcept = 0;

    virtual bool operator>(const ImmutableString& other) const noexcept = 0;
};