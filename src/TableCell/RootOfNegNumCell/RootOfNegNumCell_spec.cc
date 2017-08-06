#include "RootOfNegNumCell.h"
#include "../../It/It.h"
#include "../SingletonCell/SingletonCellSpec.mcrs"
#include "../ErrorCell/ErrorCellSpec.mcrs"
#include "../EmptyCell/EmptyCell.h"

SINGLETON_CELL_SPEC(RootOfNegNumCell, 13, "constantly returns 13 (length of \"#\\ROOT(-num)!\")")

ERROR_CELL_SPEC(RootOfNegNumCell, "constantly returns \"#\\ROOT(-num)!\"", "#\\ROOT(-num)!", 13)

TEST(RootOfNegNumCell, EmptyCellisEmptyCell) {
    IT("returns false");

    for(size_t i = 0; i < 10; ++i) {
        EXPECT_FALSE(EmptyCell::isEmptyCell(RootOfNegNumCell::obtainPtr()));
    }
}