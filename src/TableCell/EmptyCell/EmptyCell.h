#pragma once

#include "../TableCell.h"
#include "../SingletonCell/SingletonCellDeclaration.mcrs"

class EmptyCell: public TableCell {
SINGLETON_CELL_DECLARATION(EmptyCell);

public:
    const Number& getValueAsNumber() const noexcept final;

    size_t calculateOutputLength() const noexcept final;

    size_t calculateSerializedLength() const noexcept final;

private:
    static const Number emptyCellNumberValue;
};