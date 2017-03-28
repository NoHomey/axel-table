#include "StringObject.h"
#include "gtest/gtest.h"
#include "../It/It.h"

TEST(StringObject, length) {
    StringObject str;
    EXPECT_EQ(str.length(), 0);

    StringObject str2 = "1234.56789";
    EXPECT_EQ(str2.length(), 10);

    StringObject str3 = "";
    EXPECT_EQ(str3.length(), 0);

    StringObject str4 = "This is a \"String\"!";
    EXPECT_EQ(str4.length(), 19);

    StringObject str5 = "549589358935";
    EXPECT_EQ(str5.length(), 12);
}