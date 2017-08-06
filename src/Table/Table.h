#pragma once

#include "../Container/IndexedDynamicArray/IndexedDynamicArray.htd"
#include "./Row/Row.h"
#include "../TableCell/TableCell.h"

class Table {
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

    void edit(const TableIndex& index, const TableCell* cellPtr);

    const TableCell* operator[](const TableIndex& index) const;

#ifdef __TEST__
    const IndexedDynamicArray<Row*>& getRows() const noexcept {
        return tableRows;
    }
#endif

private:
    IndexedDynamicArray<Row*> tableRows;
};