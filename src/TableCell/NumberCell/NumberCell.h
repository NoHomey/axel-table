#pragma once

#include "../TableCell.h"

class NumberCell: public TableCell {
public:
    NumberCell(const Number& number) noexcept;
    
    const Number& getValueAsNumber() const noexcept final;

private:
    Number value;
};