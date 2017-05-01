#pragma once

#include "../TypeParser/TypeParser.h"

class DoubleParser: public TypeParser<double> {
public:
    DoubleParser(ConstString& string) noexcept;

    DoubleParser(const DoubleParser&) = delete;

    DoubleParser(DoubleParser&&) = delete;

    DoubleParser& operator=(const DoubleParser&) = delete;

    DoubleParser& operator=(DoubleParser&&) = delete;
    
protected:
    void typeValidator() const override final;

    double typeParser() const override final;

private:
    double parseFloatingPart(const size_t floatingPartBeginning) const noexcept;

    static const size_t TOTAL_DIGITS_COUNT;
};