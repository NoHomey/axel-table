#include "NumberCell.h"
#include "gtest/gtest.h"
#include "../../It/It.h"

TEST(NumberCell, conversionToNumber) {
    IT("should equal to the Number with which it was created");
    NumberCell cell = {{}};
    EXPECT_EQ(static_cast<Number>(cell).getInteger(), 0);
    NumberCell cell1 = {(long long)9};
    EXPECT_EQ(static_cast<Number>(cell1).getInteger(), 9);
    NumberCell cell2 = {(long long)27};
    EXPECT_EQ(static_cast<Number>(cell2).getInteger(), 27);
    NumberCell cell3 = {(long long)30};
    EXPECT_EQ(static_cast<Number>(cell3).getInteger(), 30);
    NumberCell cell4 = {(long long)-54};
    EXPECT_EQ(static_cast<Number>(cell4).getInteger(), -54);
    NumberCell cell5 = {2.345};
    EXPECT_DOUBLE_EQ(static_cast<Number>(cell5).getReal(), 2.345);
    NumberCell cell6 = {-2.345};
    EXPECT_DOUBLE_EQ(static_cast<Number>(cell6).getReal(), -2.345);
    NumberCell cell7 = {0.5};
    EXPECT_DOUBLE_EQ(static_cast<Number>(cell7).getReal(), 0.5);
}