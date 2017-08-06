#include "CircRefCell.h"
#include "../../It/It.h"
#include "../SingletonCell/SingletonCellSpec.mcrs"
#include "../ErrorCell/ErrorCellSpec.mcrs"
#include "../EmptyCell/EmptyCell.h"

SINGLETON_CELL_SPEC(CircRefCell, 9, "constantly returns 9 (length of \"#CIRCREF!\")")

ERROR_CELL_SPEC(CircRefCell, "constantly returns \"#CircRef!\"", "#CIRCREF!", 9)

TEST(CircRefCell, EmptyCellisEmptyCell) {
    IT("returns false");

    for(size_t i = 0; i < 10; ++i) {
        EXPECT_FALSE(EmptyCell::isEmptyCell(CircRefCell::obtainPtr()));
    }
}