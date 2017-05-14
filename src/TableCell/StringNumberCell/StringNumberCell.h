#pragma once

#include "../NumberCell/NumberCell.h"

class StringNumberCell: public NumberCell {
public:
    StringNumberCell(const Number& number) noexcept;
};