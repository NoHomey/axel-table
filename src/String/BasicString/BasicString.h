#pragma once

#include "../ImmutableString.h"

#include "../../Exception.h"

template<typename CString>
class BasicString: public ImmutableString {
public:
    class BadStringOffset: public Exception { };

    BasicString() noexcept;

    BasicString(CString cstring) noexcept;

    BasicString(const BasicString& other, const size_t offset, const bool fromEnd = false);

    virtual ~BasicString() noexcept;
    
    BasicString(const BasicString&) = delete;

    BasicString& operator=(const BasicString&) = delete;

    bool isNull() const noexcept override final;

    bool isEmpty() const noexcept override final;

    bool hasContent() const noexcept override final;

    virtual size_t length() const noexcept override final;

    const char* cString() const noexcept override final;

    char operator[](const size_t index) const noexcept override final;

    bool operator==(const ImmutableString& other) const noexcept override final;

    bool operator!=(const ImmutableString& other) const noexcept override final;

    bool operator<(const ImmutableString& other) const noexcept override final;

    bool operator>(const ImmutableString& other) const noexcept override final;

protected:
    static size_t calculateLength(CString cstring) noexcept;

    explicit BasicString(CString cstring, const size_t cstrLength) noexcept;

    CString string;

    const size_t stringLength;
};