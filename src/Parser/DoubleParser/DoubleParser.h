#pragma once

#include "../TypeParser/TypeParser.h"

class DoubleParser: public TypeParser<double> {
public:
    DoubleParser(ConstString& string) noexcept;

    DoubleParser(const DoubleParser&) = delete;

    DoubleParser& operator=(const DoubleParser&) = delete;
    
protected:
    void typeValidator() const override final;

    double typeParser() const override final;
};