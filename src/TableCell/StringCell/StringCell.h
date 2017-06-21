#pragma once

#include "../TableCell.h"
#include "../../String/FixedSizeString/FixedSizeString.h"

class StringCell: public TableCell {
public:
    StringCell(FixedSizeString&& string) noexcept;
    
    const Number& getValueAsNumber() const noexcept final;

    size_t calculateOutputLength() const noexcept final;

    size_t calculateSerializedLength() const noexcept final;

private:
    static bool shouldBeEscaped(char symbol) noexcept;

    size_t calculateNumberOfCharsToBeEscaped() const noexcept;

    FixedSizeString value;
};