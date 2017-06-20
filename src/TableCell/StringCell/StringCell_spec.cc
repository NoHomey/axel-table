#include "StringCell.h"
#include "gtest/gtest.h"
#include "../../It/It.h"

TEST(StringCell, conversionToNumber) {
    IT("should always return 0");
    FixedSizeString str{3};
    str << 'i' << 'v' << 'o';
    StringCell cell = {std::move(str)};
    EXPECT_EQ(static_cast<Number>(cell).getInteger(), 0);
    FixedSizeString str2{0};
    StringCell cell2 = {std::move(str)};
    EXPECT_EQ(static_cast<Number>(cell).getInteger(), 0);
    FixedSizeString str3{1};
    str3 << 'i';
    StringCell cell3 = {std::move(str)};
    EXPECT_EQ(static_cast<Number>(cell).getInteger(), 0);
}