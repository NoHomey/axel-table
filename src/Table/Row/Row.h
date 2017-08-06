#pragma once

#include "../../Container/IndexedDynamicArray/IndexedDynamicArray.htd"
#include "../../TableCell/TableCell.h"

class Row {
public:
    ~Row() noexcept;

    size_t length() const noexcept;

    void edit(const size_t index, const TableCell* cellPtr);

    const TableCell* cellAt(const size_t index) const;

#ifdef __TEST__
    const IndexedDynamicArray<const TableCell*>& getCells() const noexcept {
        return cells;
    }
#endif

private:
    IndexedDynamicArray<const TableCell*> cells;
};