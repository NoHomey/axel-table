#pragma once

#include "../Container/FragmentedDynamicArray/FragmentedDynamicArray.htd"
#include "../TableCell/TableCell.h"

class Table {
using Cell = const TableCell;
using CellPtr = Cell*;
using Row = FragmentedDynamicArray<CellPtr>;
using RowPtr = Row*;
using Rows = FragmentedDynamicArray<RowPtr>;

public:
    class TableIndex {
    public:
        TableIndex(size_t row, size_t col) noexcept;

        size_t getRow() const noexcept;

        size_t getColumn() const noexcept;

    private:
        size_t rowIndex;
        size_t columnIndex;
    };

    Table() noexcept = default;

    void edit(const TableIndex& index, CellPtr cellValue);

    const TableCell& operator[](const TableIndex& index) const;

private:
    Rows rows;
};