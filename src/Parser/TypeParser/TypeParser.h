#pragma once

#include "../../String/ConstString/ConstString.h"

template<typename Type>
class TypeParser {
public:
    TypeParser(ConstString& string) noexcept;

    TypeParser(const TypeParser&) = delete;

    TypeParser& operator=(const TypeParser&) = delete;
    
    void validate();

    Type parse();

    bool isValidated() const noexcept;

protected:
    virtual void validator() const = 0;

    virtual Type parser() const = 0; 

    ConstString& token;

    bool validated;
};