#include "ErrorCell.h"
#include "../../It/It.h"
#include "../SingletonCell/SingletonCellSpec.mcrs"
#include "ErrorCellSpec.mcrs"
#include "../EmptyCell/EmptyCell.h"

SINGLETON_CELL_SPEC(ErrorCell, 7, "constantly returns 7 (length of \"#ERROR!\")")

ERROR_CELL_SPEC(ErrorCell, "constantly returns \"#ERROR!\"", "#ERROR!", 7)

TEST(ErrorCell, EmptyCellisEmptyCell) {
    IT("returns false");

    for(size_t i = 0; i < 10; ++i) {
        EXPECT_FALSE(EmptyCell::isEmptyCell(ErrorCell::obtainPtr()));
    }
}