#pragma once

#include "../ImmutableString.h"
#include "../../Container/DynamicArray/DynamicArray.htd"

class DynamicString: public ImmutableString {
private:
    using StringBuffer = DynamicArray<char>;

public:
    DynamicString() noexcept = default;

    DynamicString(const char* str);

    ~DynamicString() noexcept = default;

    DynamicString(const DynamicString&) = default;

    DynamicString(DynamicString&&) = default;

    DynamicString& operator=(const DynamicString&) = default;

    DynamicString& operator=(DynamicString&&) = default;

    bool isEmpty() const noexcept;

    size_t length() const noexcept;

    size_t capacity() const noexcept;

    const char* cString() const noexcept;

    char operator[](const size_t index) const noexcept;

    bool operator==(const ImmutableString& other) const noexcept;

    bool operator!=(const ImmutableString& other) const noexcept;

    bool operator<(const ImmutableString& other) const noexcept;

    bool operator>(const ImmutableString& other) const noexcept;

    DynamicString operator+(const ImmutableString& other) const;

    DynamicString& operator+=(const ImmutableString& other);

    void reserve(size_t size);
    
    void shrinkToFit();

    void clear() noexcept;

private:
    static size_t stringLength(const char* string) noexcept;

    static size_t stringInitialLength(const char* string) noexcept;

    StringBuffer string;
};