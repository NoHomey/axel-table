#pragma once

#include "../TableCell.h"

class NumberCell: public TableCell {
public:
    NumberCell(const Number& number) noexcept;
    
    operator Number() const noexcept final;

private:
    Number value;
};