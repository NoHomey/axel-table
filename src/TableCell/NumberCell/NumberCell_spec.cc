#include "NumberCell.h"
#include "gtest/gtest.h"
#include "../../It/It.h"

TEST(NumberCell, getValueAsNumber) {
    IT("should return the Number with which it was created");
    NumberCell cell = {{}};
    EXPECT_EQ(cell.getValueAsNumber().getInteger(), 0);
    NumberCell cell1 = {(long long)9};
    EXPECT_EQ(cell1.getValueAsNumber().getInteger(), 9);
    NumberCell cell2 = {(long long)27};
    EXPECT_EQ(cell2.getValueAsNumber().getInteger(), 27);
    NumberCell cell3 = {(long long)30};
    EXPECT_EQ(cell3.getValueAsNumber().getInteger(), 30);
    NumberCell cell4 = {(long long)-54};
    EXPECT_EQ(cell4.getValueAsNumber().getInteger(), -54);
    NumberCell cell5 = {2.345};
    EXPECT_DOUBLE_EQ(cell5.getValueAsNumber().getReal(), 2.345);
    NumberCell cell6 = {-2.345};
    EXPECT_DOUBLE_EQ(cell6.getValueAsNumber().getReal(), -2.345);
    NumberCell cell7 = {0.5};
    EXPECT_DOUBLE_EQ(cell7.getValueAsNumber().getReal(), 0.5);
}