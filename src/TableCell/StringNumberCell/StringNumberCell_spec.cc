#include "StringNumberCell.h"
#include "gtest/gtest.h"
#include "../../It/It.h"

#include "StringNumberCell.h"
#include "gtest/gtest.h"
#include "../../It/It.h"

TEST(StringNumberCell, getValueAsNumber) {
    IT("should return the Number with which it was created");
    StringNumberCell cell = {{}};
    EXPECT_EQ(cell.getValueAsNumber().getInteger(), 0);
    StringNumberCell cell1 = {(long long)9};
    EXPECT_EQ(cell1.getValueAsNumber().getInteger(), 9);
    StringNumberCell cell2 = {(long long)27};
    EXPECT_EQ(cell2.getValueAsNumber().getInteger(), 27);
    StringNumberCell cell3 = {(long long)30};
    EXPECT_EQ(cell3.getValueAsNumber().getInteger(), 30);
    StringNumberCell cell4 = {(long long)-54};
    EXPECT_EQ(cell4.getValueAsNumber().getInteger(), -54);
    StringNumberCell cell5 = {2.345};
    EXPECT_DOUBLE_EQ(cell5.getValueAsNumber().getReal(), 2.345);
    StringNumberCell cell6 = {-2.345};
    EXPECT_DOUBLE_EQ(cell6.getValueAsNumber().getReal(), -2.345);
    StringNumberCell cell7 = {0.5};
    EXPECT_DOUBLE_EQ(cell7.getValueAsNumber().getReal(), 0.5);
}