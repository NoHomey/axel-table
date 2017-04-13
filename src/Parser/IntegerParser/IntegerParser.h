#pragma once

#include "../TypeParser/TypeParser.h"

class IntegerParser: public TypeParser<int> {
public:
    IntegerParser(const StringObject& string) noexcept;

    IntegerParser(const IntegerParser&) = delete;

    IntegerParser& operator=(const IntegerParser&) = delete;

    int parse() const noexcept final;

    bool matchesType() const noexcept final;
    
protected:
    void validator() const final;

private:
    static const StringObject ABS_MAX_VALUE;
    static const size_t ABS_MAX_VALUE_LENGTH;
};