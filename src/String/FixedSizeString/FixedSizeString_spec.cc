#include "FixedSizeString.h"
#include "../ConstString/ConstString.h"
#include "gtest/gtest.h"
#include "../../It/It.h"

TEST(FixedSizeString, length) {
    IT("should return the same number of chars with which it was constructed");
    FixedSizeString str{9};
    EXPECT_EQ(str.length(), 9);
    FixedSizeString str2{14};
    EXPECT_EQ(str2.length(), 14);
}

TEST(FixedSizeString, filling) {
    FixedSizeString ivo{3};
    str << 'i' << 'v' << 'o';
    EXPECT_EQ(ivo, ConstString{"ivo"});
    FixedSizeString str{8};
    str << "fixedStr";
    EXPECT_EQ(str, ConstString{"fixedStr"});
    FixedSizeString str2{12};
    str2 << "mixed " << 's' << 't' << 'r' << "!!!";
    EXPECT_EQ(str2, ConstString{"mixed str!!!"});
    FixedSizeString full{4};
    str2 << "fully " << 's' << 't' << 'r' << "!!!";
    EXPECT_EQ(full, ConstString{"full"});
}


