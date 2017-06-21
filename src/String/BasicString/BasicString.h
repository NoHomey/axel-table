#pragma once

#include "../ImmutableString.h"

template<typename CString>
class BasicString: public ImmutableString {
public:
    BasicString(CString cstring, const size_t cstrLength) noexcept;

    virtual ~BasicString() noexcept = default;
    
    BasicString(const BasicString&) = delete;

    BasicString(BasicString&&) = delete;

    BasicString& operator=(const BasicString&) = delete;

    BasicString& operator=(BasicString&&) = delete;

    bool isEmpty() const noexcept override final;

    size_t length() const noexcept override final;

    const char* cString() const noexcept override final;

    char operator[](const size_t index) const noexcept override final;

    bool operator==(const ImmutableString& other) const noexcept override final;

    bool operator!=(const ImmutableString& other) const noexcept override final;

    bool operator<(const ImmutableString& other) const noexcept override final;

    bool operator>(const ImmutableString& other) const noexcept override final;

protected:
    static bool shouldBeNull(const char* cstring, const size_t cstrLength) noexcept;

    CString string;

    size_t stringLength;

private:
    static bool constFalse(const char a, const char b) noexcept;

    static bool lessThanOperator(const char a, const char b) noexcept;

    bool compareStrings(const ImmutableString& other, const bool onEqual,
                        bool (*onDiff)(const char a, const char b)) const noexcept;
};