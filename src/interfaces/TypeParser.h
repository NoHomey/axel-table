#pragma once

template<typename Type>
class TypeParser {
public:
    TypeParser(const char* str) noexcept
    : token{str} {}

public:
    virtual Type parse() const noexcept = 0;
    virtual bool matchesType() const noexcept = 0;
    virtual bool isValid() const noexcept = 0;
    
protected:
    const char* token;
};