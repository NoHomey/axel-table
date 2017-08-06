#pragma once

#include "../TableCell.h"
#include "../SingletonCell/SingletonCellDeclaration.mcrs"

class EmptyCell: public TableCell {
SINGLETON_CELL_DECLARATION(EmptyCell);

public:
    static bool isEmptyCell(const TableCell* cellPtr) noexcept;

    const Number& getValueAsNumber() const noexcept final;

    size_t calculateOutputLength() const noexcept final;

    size_t calculateSerializedLength() const noexcept final;

    bool isDeletable() const noexcept final;
};