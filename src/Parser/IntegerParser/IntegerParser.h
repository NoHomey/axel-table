#pragma once

#include "../TypeParser/TypeParser.h"

class IntegerParser: public TypeParser<long long> {
public:
    IntegerParser(ConstString& string) noexcept;

    IntegerParser(const IntegerParser&) = delete;

    IntegerParser& operator=(const IntegerParser&) = delete;
    
protected:
    void validator() const override final;

    long long parser() const override final;

private:
    static ConstString ABS_MAX_VALUE;
    static const size_t ABS_MAX_VALUE_LENGTH;
};