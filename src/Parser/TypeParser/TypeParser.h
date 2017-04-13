#pragma once

#include "../../String/StringObject/StringObject.h"

template<typename Type>
class TypeParser {
public:
    TypeParser(const StringObject& string) noexcept;

    TypeParser(const TypeParser&) = delete;

    TypeParser& operator=(const TypeParser&) = delete;

    virtual Type parse() const noexcept = 0;

    virtual bool matchesType() const noexcept = 0;
    
    void validate();

    bool isValidated() const noexcept;

protected:
    virtual void validator() const = 0;

    const StringObject& token;

    bool validated;
};