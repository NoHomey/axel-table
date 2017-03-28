#pragma once

#include "../interfaces/TypeParser.h"
#include "../StringObject/StringObject.h"

class IntegerParser: public TypeParser<int> {
public:
    IntegerParser(const StringObject& string) noexcept;

    int parse() const noexcept final;
    bool matchesType() const noexcept final;
    bool isValid() const noexcept final;

private:
    StringObject& token;
};