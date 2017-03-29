#pragma once

#include <cstddef>

class String {
public:
    String() noexcept = default;

    virtual ~String() noexcept = default;

    String(const String& other) = delete;

    String& operator=(const String& other) = delete;

    virtual bool isNull() const noexcept = 0;

    virtual bool isEmpty() const noexcept = 0;

    virtual bool hasContent() const noexcept = 0;

    virtual size_t length() const noexcept = 0;

    virtual const char* cString() const noexcept = 0;

    virtual char operator[](const size_t index) const noexcept = 0;

    virtual bool operator==(const String& other) const noexcept = 0;

    virtual bool operator!=(const String& other) const noexcept = 0;

    virtual bool operator<(const String& other) const noexcept = 0;

    virtual bool operator>(const String& other) const noexcept = 0;
};