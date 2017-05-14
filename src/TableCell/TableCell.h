#pragma once

#include "../Number/Number.h"

class TableCell {
public:
    TableCell() noexcept = default;

    virtual operator Number() const noexcept = 0;
};