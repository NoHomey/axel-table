#include "FixedSizeString.h"
#include "gtest/gtest.h"
#include "../../It/It.h"

TEST(FixedSizeString, length) {
    IT("should return the same number of chars with which it was constructed");
    FixedSizeString str{9};
    EXPECT_EQ(str.length(), 9);
    FixedSizeString str2{14};
    EXPECT_EQ(str2.length(), 14);
}


