#pragma once

#include "../ImmutableString.h"

template<typename CString>
class BasicString: public ImmutableString {
public:
    BasicString() noexcept;

    BasicString(CString cstring) noexcept;

    virtual ~BasicString() noexcept;
    
    BasicString(const BasicString& other) = delete;

    BasicString& operator=(const BasicString& other) = delete;

    bool isNull() const noexcept final;

    bool isEmpty() const noexcept final;

    bool hasContent() const noexcept final;

    size_t length() const noexcept final;

    const char* cString() const noexcept final;

    char operator[](const size_t index) const noexcept final;

    bool operator==(const ImmutableString& other) const noexcept final;

    bool operator!=(const ImmutableString& other) const noexcept final;

    bool operator<(const ImmutableString& other) const noexcept final;

    bool operator>(const ImmutableString& other) const noexcept final;

protected:
    CString string;
};