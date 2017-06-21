#pragma once

#include "../TableCell.h"

class NumberCell: public TableCell {
public:
    NumberCell(const Number& number) noexcept;

    virtual ~NumberCell() noexcept = default;
    
    const Number& getValueAsNumber() const noexcept final;

    size_t calculateOutputLength() const noexcept override;

    size_t calculateSerializedLength() const noexcept final;

private:
    static char fpconv_buffer[24];

    size_t calculateIntegerOutputLength() const noexcept;

    size_t calculateRealOutputLength() const noexcept;

    Number value;
};