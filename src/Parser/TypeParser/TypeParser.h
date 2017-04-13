#pragma once

#include "../../String/StringObject/StringObject.h"

template<typename Type>
class TypeParser {
public:
    TypeParser(const StringObject& string) noexcept;

    TypeParser(const TypeParser&) = delete;

    TypeParser& operator=(const TypeParser&) = delete;

    virtual bool matchesType() const noexcept = 0;
    
    void validate();

    Type parse();

    bool isValidated() const noexcept;

protected:
    virtual void validator() const = 0;

    virtual Type parser() const = 0; 

    const StringObject& token;

    bool validated;
};