#pragma once

#include "../TableCell.h"
#include "../../String/FixedSizeString/FixedSizeString.h"

class StringCell: public TableCell {
public:
    StringCell(FixedSizeString&& string) noexcept;
    
    const Number& getValueAsNumber() const noexcept final;

private:
    static const Number stringNumberValue;

    FixedSizeString value;
};