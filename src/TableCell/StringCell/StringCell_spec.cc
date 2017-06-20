#include "StringCell.h"
#include "gtest/gtest.h"
#include "../../It/It.h"

TEST(StringCell, getValueAsNumber) {
    IT("constantly return Number instance with Value integer 0");
    FixedSizeString str{3};
    str << 'i' << 'v' << 'o';
    StringCell cell = {std::move(str)};
    EXPECT_EQ(cell.getValueAsNumber().getInteger(), 0);
    FixedSizeString str2{0};
    StringCell cell2 = {std::move(str)};
    EXPECT_EQ(cell2.getValueAsNumber().getInteger(), 0);
    FixedSizeString str3{1};
    str3 << 'i';
    StringCell cell3 = {std::move(str)};
    EXPECT_EQ(cell3.getValueAsNumber().getInteger(), 0);
}