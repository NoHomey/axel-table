#include "StringNumberCell.h"
#include "gtest/gtest.h"
#include "../../It/It.h"

TEST(StringNumberCell, conversionToNumber) {
    IT("should equal to the Number with which it was created");
    StringNumberCell cell = {{}};
    EXPECT_EQ(static_cast<Number>(cell).getInteger(), 0);
    StringNumberCell cell1 = {(long long)9};
    EXPECT_EQ(static_cast<Number>(cell1).getInteger(), 9);
    StringNumberCell cell2 = {(long long)27};
    EXPECT_EQ(static_cast<Number>(cell2).getInteger(), 27);
    StringNumberCell cell3 = {(long long)30};
    EXPECT_EQ(static_cast<Number>(cell3).getInteger(), 30);
    StringNumberCell cell4 = {(long long)-54};
    EXPECT_EQ(static_cast<Number>(cell4).getInteger(), -54);
    StringNumberCell cell5 = {2.345};
    EXPECT_DOUBLE_EQ(static_cast<Number>(cell5).getReal(), 2.345);
    StringNumberCell cell6 = {-2.345};
    EXPECT_DOUBLE_EQ(static_cast<Number>(cell6).getReal(), -2.345);
    StringNumberCell cell7 = {0.5};
    EXPECT_DOUBLE_EQ(static_cast<Number>(cell7).getReal(), 0.5);
}