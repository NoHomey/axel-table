#pragma once

#include <cstddef>

class StringObject {
public:
    StringObject() noexcept;

    StringObject(const char* cstring) noexcept;

    virtual ~StringObject() noexcept;

    StringObject(const StringObject& other) noexcept;

    StringObject& operator=(const StringObject& other) = delete;

    bool isNull() const noexcept;

    bool isEmpty() const noexcept;

    size_t length() const noexcept;

    const char* cString() const noexcept;

    char operator[](const size_t index) const noexcept;

    bool operator==(const StringObject& other) const noexcept;

    bool operator!=(const StringObject& other) const noexcept;

    /*bool operator<(const StringObject& other) const noexcept;

    bool operator>(const StringObject& other) const noexcept;*/

protected:
    char* string;
};