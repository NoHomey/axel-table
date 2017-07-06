#pragma once

#include <cstddef>

class ImmutableString {
public:
    ImmutableString() noexcept = default;

    virtual ~ImmutableString() noexcept = default;

    ImmutableString(const ImmutableString&) = delete;

    ImmutableString(ImmutableString&&) = delete;

    ImmutableString& operator=(const ImmutableString&) = delete;

    ImmutableString& operator=(ImmutableString&&) = delete;

    virtual bool isEmpty() const noexcept = 0;

    virtual size_t length() const noexcept = 0;

    virtual const char* cString() const noexcept = 0;

    virtual char operator[](const size_t index) const noexcept = 0;

    virtual bool operator==(const ImmutableString& other) const noexcept = 0;

    virtual bool operator!=(const ImmutableString& other) const noexcept = 0;

    virtual bool operator<(const ImmutableString& other) const noexcept = 0;

    virtual bool operator>(const ImmutableString& other) const noexcept = 0;
};