#pragma once

#include "../TypeParser.h"
#include "../../String/StringObject/StringObject.h"

class IntegerParser: public TypeParser<int> {
public:
    IntegerParser(const StringObject& string) noexcept;

    IntegerParser(const IntegerParser&) = delete;

    IntegerParser& operator=(const IntegerParser&) = delete;

    int parse() const noexcept final;

    bool matchesType() const noexcept final;
    
    bool isValid() const noexcept final;

private:
    const StringObject& token;
};