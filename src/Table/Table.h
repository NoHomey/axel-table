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

    ~Table() noexcept;

    size_t getRowsCount() const noexcept;

    size_t getColumnsCount() const noexcept;

    void edit(const TableIndex& index, CellPtr cellPtr);

    const TableCell& operator[](const TableIndex& index) const;

#ifdef __TEST__
    const Rows& getRows() const noexcept {
        return tableRows;
    }
#endif

private:
    static void deleteIfDeletable(CellPtr cellPtr) noexcept;

    static bool isEmptyCell(CellPtr cellPtr) noexcept;

    static bool clean(const RowPtr rowPtr, size_t index) noexcept;

    static void removeEmptyCells(const RowPtr rowPtr) noexcept;

    Rows tableRows;
};