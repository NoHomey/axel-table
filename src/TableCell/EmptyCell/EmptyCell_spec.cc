#include "EmptyCell.h"
#include "../../It/It.h"
#include "../SingletonCell/SingletonCellSpec.mcrs"

SINGLETON_CELL_SPEC(EmptyCell, 0, "constantly returns 0 (length of \"\")")

TEST(EmptyCell, getValueAsNumber) {
    IT("constantly return Number instance with Value integer 0");

    for(size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(EmptyCell::obtainRef().getValueAsNumber().getInteger(), 0);
    }
}

TEST(EmptyCell, isDeletable) {
    IT("returns false");

    for(size_t i = 0; i < 10; ++i) {
        EXPECT_FALSE(EmptyCell::obtainRef().isDeletable());
    }
}