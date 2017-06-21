#pragma once

#include <cstddef>
#include "../Number/Number.h"

class TableCell {
public:
    TableCell() noexcept = default;

    virtual ~TableCell() noexcept = default; 

    virtual const Number& getValueAsNumber() const = 0;

    virtual size_t calculateOutputLength() const noexcept = 0;

    virtual size_t calculateSerializedLength() const noexcept = 0;

    virtual bool isDeletable() const noexcept;
};