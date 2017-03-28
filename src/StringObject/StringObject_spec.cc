#include "StringObject.h"
#include "gtest/gtest.h"
#include "../It/It.h"

TEST(StringObject, isNull) {
    IT("should return true if string internally is nullptr");
    StringObject str;
    EXPECT_TRUE(str.isNull());
    EXPECT_TRUE(StringObject().isNull());

    StringObject str2 = "1234.56789";
    EXPECT_FALSE(str2.isNull());

    StringObject str3 = "";
    EXPECT_FALSE(str3.isNull());

    StringObject str4 = "This is a \"String\"!";
    EXPECT_FALSE(str4.isNull());
}

TEST(StringObject, isEmpty) {
    IT("should return true if string is a empty string");
    StringObject str;
    EXPECT_FALSE(str.isEmpty());
    EXPECT_FALSE(StringObject().isEmpty());
    EXPECT_FALSE(StringObject("0").isEmpty());

    StringObject str2 = "1234.56789";
    EXPECT_FALSE(str2.isEmpty());

    StringObject str3 = "";
    EXPECT_TRUE(str3.isEmpty());
    EXPECT_TRUE(StringObject("\0").isEmpty());
    EXPECT_TRUE(StringObject("\0sfdsda").isEmpty());

    StringObject str4 = "This is a \"String\"!";
    EXPECT_FALSE(str4.isEmpty());
}

TEST(StringObject, length) {
    IT("should return the number of chars before \\0");
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

TEST(String, cString) {
    IT("should return a non-modifiable standard C character array version of the string");
    StringObject str;
    EXPECT_EQ(str.cString(), nullptr);

    const char* data = "1234.56789";
    StringObject str2 = data;
    EXPECT_EQ(str2.cString(), data);
}

TEST(String, indexOperator) {
    IT("should return char at the given position or \0 if index is out of range");
    StringObject str;
    EXPECT_EQ(str[0], '\0');
    EXPECT_EQ(str[9], '\0');

    const char* data = "1234.56789";
    StringObject str2 = data;
    for(size_t i = 0; data[i] != '\0'; ++i) {
        EXPECT_EQ(str2[i], data[i]);
    }
    EXPECT_EQ(str2[10], '\0');
    EXPECT_EQ(str2[100], '\0');
}

TEST(String, equalityOperators) {
    IT("should compare dose two strings have equal value");
    EXPECT_EQ(StringObject("1234.56789"), StringObject("1234.56789"));
    EXPECT_EQ(StringObject(), StringObject());
    EXPECT_EQ(StringObject(""), StringObject(""));
    EXPECT_EQ(StringObject("text"), StringObject("text"));
    EXPECT_EQ(StringObject("Verry verry long text :)"), StringObject("Verry verry long text :)"));
    EXPECT_EQ(StringObject(""), StringObject());
    EXPECT_NE(StringObject(""), StringObject("0"));
    EXPECT_NE(StringObject("12345"), StringObject("123.45"));
    EXPECT_NE(StringObject("txt"), StringObject("text"));
    EXPECT_NE(StringObject("-235435"), StringObject("+235435"));
}