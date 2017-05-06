#pragma once

#include "../../String/ConstString/ConstString.h"

template<typename Type>
class TypeParser {
public:
    TypeParser(ConstString& string) noexcept;

    TypeParser(const TypeParser&) = delete;

    TypeParser(TypeParser&&) = delete;

    TypeParser& operator=(const TypeParser&) = delete;

    TypeParser& operator=(TypeParser&&) = delete;

    Type parseType() const;

    void validateType() const;

protected:
    virtual void typeValidator() const = 0;

    virtual Type typeParser() const = 0; 

    ConstString& token;
};