#include "StringNumberCell.h"
#include "gtest/gtest.h"
#include "../../It/It.h"
#include "../../Number/NumberHelper.h"

TEST(StringNumberCell, conversionToNumber) {
    IT("should equal to the Number with which it was created");
    StringNumberCell cell = {{}};
    EXPECT_EQ(NumberHelper{cell}.getInteger(), 0);
    StringNumberCell cell1 = {(long long)9};
    EXPECT_EQ(NumberHelper{cell1}.getInteger(), 9);
    StringNumberCell cell2 = {(long long)27};
    EXPECT_EQ(NumberHelper{cell2}.getInteger(), 27);
    StringNumberCell cell3 = {(long long)30};
    EXPECT_EQ(NumberHelper{cell3}.getInteger(), 30);
    StringNumberCell cell4 = {(long long)-54};
    EXPECT_EQ(NumberHelper{cell4}.getInteger(), -54);
    StringNumberCell cell5 = {2.345};
    EXPECT_DOUBLE_EQ(NumberHelper{cell5}.getReal(), 2.345);
    StringNumberCell cell6 = {-2.345};
    EXPECT_DOUBLE_EQ(NumberHelper{cell6}.getReal(), -2.345);
    StringNumberCell cell7 = {0.5};
    EXPECT_DOUBLE_EQ(NumberHelper{cell7}.getReal(), 0.5);
}