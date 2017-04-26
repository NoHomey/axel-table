#pragma once

#include "../TypeParser/TypeParser.h"

class IntegerParser: public TypeParser<int> {
public:
    IntegerParser(ConstString& string) noexcept;

    IntegerParser(const IntegerParser&) = delete;

    IntegerParser& operator=(const IntegerParser&) = delete;

    bool matchesType() const noexcept final;
    
protected:
    void validator() const final;

    int parser() const final;

private:
    static ConstString ABS_MAX_VALUE;
    static const size_t ABS_MAX_VALUE_LENGTH;
};