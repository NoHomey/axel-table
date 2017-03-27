#pragma once

#include "../interfaces/TypeParser.h"

class IntegerParser: public TypeParser<int> {
public:
    IntegerParser(const char* token) noexcept;

    int parse() const noexcept final;
    bool matchesType() const noexcept final;
    bool isValid() const noexcept final;
};