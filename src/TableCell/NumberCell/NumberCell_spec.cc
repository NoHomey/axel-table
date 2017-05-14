#include "NumberCell.h"
#include "gtest/gtest.h"
#include "../../It/It.h"
#include "../../Number/NumberHelper.h"

TEST(NumberCell, conversionToNumber) {
    IT("should equal to the Number with which it was created");
    NumberCell cell = {{}};
    EXPECT_EQ(NumberHelper{cell}.getInteger(), 0);
    NumberCell cell1 = {(long long)9};
    EXPECT_EQ(NumberHelper{cell1}.getInteger(), 9);
    NumberCell cell2 = {(long long)27};
    EXPECT_EQ(NumberHelper{cell2}.getInteger(), 27);
    NumberCell cell3 = {(long long)30};
    EXPECT_EQ(NumberHelper{cell3}.getInteger(), 30);
    NumberCell cell4 = {(long long)-54};
    EXPECT_EQ(NumberHelper{cell4}.getInteger(), -54);
    NumberCell cell5 = {2.345};
    EXPECT_DOUBLE_EQ(NumberHelper{cell5}.getReal(), 2.345);
    NumberCell cell6 = {-2.345};
    EXPECT_DOUBLE_EQ(NumberHelper{cell6}.getReal(), -2.345);
    NumberCell cell7 = {0.5};
    EXPECT_DOUBLE_EQ(NumberHelper{cell7}.getReal(), 0.5);
}