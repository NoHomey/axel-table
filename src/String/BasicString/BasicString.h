#pragma once

#include "../ImmutableString.h"

template<typename CString>
class BasicString: public ImmutableString {
public:
    BasicString() noexcept;

    BasicString(CString cstring) noexcept;

    virtual ~BasicString() noexcept;
    
    BasicString(const BasicString&) = delete;

    BasicString& operator=(const BasicString&) = delete;

    bool isNull() const noexcept override final;

    bool isEmpty() const noexcept override final;

    bool hasContent() const noexcept override final;

    virtual size_t length() const noexcept override;

    const char* cString() const noexcept override final;

    char operator[](const size_t index) const noexcept override final;

    bool operator==(const ImmutableString& other) const noexcept override final;

    bool operator!=(const ImmutableString& other) const noexcept override final;

    bool operator<(const ImmutableString& other) const noexcept override final;

    bool operator>(const ImmutableString& other) const noexcept override final;

protected:
    CString string;
};