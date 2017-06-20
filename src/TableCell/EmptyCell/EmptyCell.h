#pragma once

#include "../TableCell.h"

class EmptyCell: public TableCell {
public:
    const Number& getValueAsNumber() const noexcept final;

    size_t calculateOutputLength() const noexcept final;

    size_t calculateSerializedLength() const noexcept final;

    static const EmptyCell& obtainEmptyCellRef() noexcept;

    static const EmptyCell* obtainEmptyCellConstPtr() noexcept;

    static EmptyCell* obtainEmptyCellPtr() noexcept;

private:
    EmptyCell() noexcept;

    static const Number emptyCellNumberValue;

    static EmptyCell instance;
};