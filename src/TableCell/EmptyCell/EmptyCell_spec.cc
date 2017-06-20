#include "EmptyCell.h"
#include "gtest/gtest.h"
#include "../../It/It.h"

TEST(EmptyCell, Singletoness) {
    IT("should be none lazy Singletone");

    EXPECT_EQ(&EmptyCell::obtainEmptyCellRef(), &EmptyCell::obtainEmptyCellRef());
    EXPECT_EQ(EmptyCell::obtainEmptyCellConstPtr(), EmptyCell::obtainEmptyCellConstPtr());
    EXPECT_EQ(EmptyCell::obtainEmptyCellPtr(), EmptyCell::obtainEmptyCellPtr());

    EXPECT_EQ(&EmptyCell::obtainEmptyCellRef(), EmptyCell::obtainEmptyCellConstPtr());
    EXPECT_EQ(EmptyCell::obtainEmptyCellConstPtr(), EmptyCell::obtainEmptyCellConstPtr());
    EXPECT_EQ(&EmptyCell::obtainEmptyCellRef(), EmptyCell::obtainEmptyCellPtr());
}

TEST(EmptyCell, getValueAsNumber) {
    IT("constantly return Number instance with Value integer 0");

    for(size_t i = 0; i < 9999999; ++i) {
        EXPECT_EQ(EmptyCell::obtainEmptyCellRef().getValueAsNumber().getInteger(), 0);
    }
}

TEST(EmptyCell, calculateOutputLength) {
    IT("constantly returns 0");

    for(size_t i = 0; i < 9999999; ++i) {
        EXPECT_EQ(EmptyCell::obtainEmptyCellRef().calculateOutputLength(), 0);
    }
}

TEST(EmptyCell, calculateSerializedLength) {
    IT("constantly returns 0");

    for(size_t i = 0; i < 9999999; ++i) {
        EXPECT_EQ(EmptyCell::obtainEmptyCellRef().calculateSerializedLength(), 0);
    }
}