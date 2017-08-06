#include "DivByZeroCell.h"
#include "../../It/It.h"
#include "../SingletonCell/SingletonCellSpec.mcrs"
#include "../ErrorCell/ErrorCellSpec.mcrs"
#include "../EmptyCell/EmptyCell.h"

SINGLETON_CELL_SPEC(DivByZeroCell, 7, "constantly returns 7 (length of \"#DIV/0!\")")

ERROR_CELL_SPEC(DivByZeroCell, "constantly returns \"#DIV/0!\"", "#DIV/0!", 7)

TEST(DivByZeroCell, EmptyCellisEmptyCell) {
    IT("returns false");

    for(size_t i = 0; i < 10; ++i) {
        EXPECT_FALSE(EmptyCell::isEmptyCell(DivByZeroCell::obtainPtr()));
    }
}