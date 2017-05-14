#pragma once

#include "../TableCell.h"
#include "../../String/FixedSizeString/FixedSizeString.h"

class StringCell: public TableCell {
public:
    StringCell(FixedSizeString&& string) noexcept;
    
    operator Number() const noexcept final;

private:
    FixedSizeString value;
};