#pragma once

#include "../NumberCell/NumberCell.h"

class StringNumberCell: public NumberCell {
public:
    StringNumberCell(const Number& number) noexcept;

    size_t calculateOutputLength() const noexcept final;
};