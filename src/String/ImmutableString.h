#pragma once

#include <cstddef>

class ImmutableString {
public:
    ImmutableString() noexcept = default;

    virtual ~ImmutableString() noexcept = default;

    ImmutableString(const ImmutableString& other) = delete;

    ImmutableString& operator=(const ImmutableString& other) = delete;

    virtual bool isNull() const noexcept = 0;

    virtual bool isEmpty() const noexcept = 0;

    virtual bool hasContent() const noexcept = 0;

    virtual size_t length() const noexcept = 0;

    virtual const char* cString() const noexcept = 0;

    virtual char operator[](const size_t index) const noexcept = 0;

    virtual bool operator==(const ImmutableString& other) const noexcept = 0;

    virtual bool operator!=(const ImmutableString& other) const noexcept = 0;

    virtual bool operator<(const ImmutableString& other) const noexcept = 0;

    virtual bool operator>(const ImmutableString& other) const noexcept = 0;
};