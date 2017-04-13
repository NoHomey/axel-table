#pragma once

template<typename Type>
class TypeParser {
public:
    TypeParser() = default;

    TypeParser(const TypeParser&) = delete;

    TypeParser& operator=(const TypeParser&) = delete;

    virtual Type parse() const noexcept = 0;

    virtual bool matchesType() const noexcept = 0;
    
    virtual void validate() const = 0;
};