#pragma once

#include "../TypeParser/TypeParser.h"
#include "../../Number/Number.h"

class NumberParser: public TypeParser<Number> {
public:
    NumberParser(ConstString& string) noexcept;

    NumberParser(const NumberParser&) = delete;

    NumberParser(NumberParser&&) = delete;

    NumberParser& operator=(const NumberParser&) = delete;

    NumberParser& operator=(NumberParser&&) = delete;
    
protected:
    void typeValidator() const override final;

    Number typeParser() const override final;
};