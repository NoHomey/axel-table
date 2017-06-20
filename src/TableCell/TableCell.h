#pragma once

#include <cstddef>
#include "../Number/Number.h"

class TableCell {
public:
    TableCell() noexcept = default;

    virtual const Number& getValueAsNumber() const noexcept = 0;
};