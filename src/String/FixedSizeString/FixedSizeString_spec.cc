#include "FixedSizeString.h"
#include "../ConstString/ConstString.h"
#include "gtest/gtest.h"
#include "../../It/It.h"

TEST(FixedSizeString, forceDynamics) {
    char str[4] = "Ivo";
    BasicString<char*>* basePtr = new BasicString<char*>{str, 3};
    delete basePtr;
    const ImmutableString* ptr = new FixedSizeString{3};
    delete ptr;
}

TEST(FixedSizeString, withZeroLength) {
    FixedSizeString str{0};
    EXPECT_TRUE(str.isEmpty());
    EXPECT_TRUE(str.isFilled());
    EXPECT_EQ(str.length(), 0);
    EXPECT_EQ(str.cString(), nullptr);
}

TEST(FixedSizeString, isEmpty) {
    FixedSizeString str{3};
    EXPECT_FALSE(str.isEmpty());
    EXPECT_FALSE(str.isFilled());
    str << 'i' << 'v';
    EXPECT_FALSE(str.isFilled());
    EXPECT_FALSE(str.isFilled());
    str << 'o';
    EXPECT_TRUE(str.isFilled());
    EXPECT_TRUE(str.isFilled());
}

TEST(FixedSizeString, length) {
    FixedSizeString str{3};
    EXPECT_EQ(str.length(), 3);
    EXPECT_FALSE(str.isFilled());
    str << 'i' << 'v';
    EXPECT_FALSE(str.isFilled());
    str << 'o';
    EXPECT_TRUE(str.isFilled());
    FixedSizeString str2{4};
    EXPECT_EQ(str2.length(), 4);
    EXPECT_FALSE(str2.isFilled());
    str2 << 'a';
    EXPECT_FALSE(str2.isFilled());
    str2 << 'b' << 'c';
    EXPECT_FALSE(str2.isFilled());
    str2 << 'd';
    EXPECT_TRUE(str2.isFilled());
    FixedSizeString empty{0};
    EXPECT_EQ(empty.length(), 0);
}

TEST(FixedSizeString, cString) {
    FixedSizeString str1{3};
    const char* data = str1.cString();
    str1 << 'a';
    EXPECT_EQ(data[0], 'a');
    str1 << 'b';
    EXPECT_EQ(data[1], 'b');
    str1 << 'c';
    EXPECT_EQ(data[2], 'c');
    EXPECT_EQ(data[3], '\0');
    FixedSizeString empty{0};
    EXPECT_EQ(empty.cString(), nullptr);
}

TEST(FixedSizeString, indexOperator) {
    FixedSizeString str1{3};
    str1 << 'a' << 'b' << 'c';
    EXPECT_EQ(str1[0], 'a');
    EXPECT_EQ(str1[1], 'b');
    EXPECT_EQ(str1[2], 'c');
    EXPECT_EQ(str1[3], '\0');
    FixedSizeString empty{0};
    EXPECT_EQ(empty[0], '\0');
    EXPECT_EQ(empty[1], '\0');
    EXPECT_EQ(empty[2], '\0');
}

TEST(FixedSizeString, equalityOperators) {
    FixedSizeString str1{3};
    str1 << 'a' << 'b' << 'c';
    FixedSizeString str2{3};
    str2 << 'a' << 'b' << 'c';
    FixedSizeString str3{3};
    str2 << 'a' << 'b' << 'd';
    ConstString str = {"abc", 3};
    FixedSizeString empty{0};
    EXPECT_TRUE(str1 == str2);
    EXPECT_TRUE(str1 == str);
    EXPECT_TRUE(str2 == str);
    EXPECT_TRUE(str1 != str3);
    EXPECT_TRUE(str != str3);
    EXPECT_TRUE(str2 != str3);
    EXPECT_TRUE(str2 == str1);
    EXPECT_TRUE(str == str1);
    EXPECT_TRUE(str == str2);
    EXPECT_TRUE(str3 != str1);
    EXPECT_TRUE(str3 != str2);
    EXPECT_TRUE(str3 != str);
    EXPECT_TRUE(str != empty);
    EXPECT_EQ(empty, (ConstString{"", 0}));
}

TEST(FixedSizeString, lessThanOperator) {
    FixedSizeString str1{3};
    str1 << 'a' << 'b' << 'c';
    FixedSizeString str2{3};
    str2 << 'a' << 'b' << 'd';
    ConstString str = {"abf", 3};
    EXPECT_TRUE(str1 < str2);
    EXPECT_TRUE(str1 < str);
    EXPECT_TRUE(str2 < str);
}

TEST(FixedSizeString, greaterThanOperator) {
    FixedSizeString str1{3};
    str1 << 'a' << 'b' << 'e';
    FixedSizeString str2{3};
    str2 << 'a' << 'b' << 'd';
    ConstString str = {"abc", 3};
    EXPECT_TRUE(str1 > str2);
    EXPECT_TRUE(str1 > str);
    EXPECT_TRUE(str2 > str);
}

TEST(FixedSizeString, filling) {
    FixedSizeString ivo{3};
    ivo << 'i' << 'v' << 'o';
    EXPECT_TRUE(ivo.isFilled());
    EXPECT_TRUE(ivo == (ConstString{"ivo", 3}));
    FixedSizeString str{8};
    str << 'f' << 'i' << 'x' << 'e' << 'd' << 'S' << 't' << 'r';
    EXPECT_TRUE(str.isFilled());
    EXPECT_TRUE(str == (ConstString{"fixedStr", 8}));
    FixedSizeString str2{13};
    str2 << 'm' << 'i' << 'x' << 'e' << 'd' << ' ';
    EXPECT_FALSE(str2.isFilled());
    str2 << 's' << 't' << 'r';
    EXPECT_FALSE(str2.isFilled());
    str2 << '!' << '!' << '!';
    EXPECT_FALSE(str2.isFilled());
    str2 << '.';
    EXPECT_TRUE(str2.isFilled());

    EXPECT_TRUE(str2 == (ConstString{"mixed str!!!.", 13}));
    FixedSizeString full{4};
    EXPECT_FALSE(full.isFilled());
    full << 'f' << 'u' << 'l' << 'l';
    EXPECT_TRUE(full.isFilled());
    full << '!' << '!';
    EXPECT_TRUE(full.isFilled());
    EXPECT_TRUE(full == (ConstString{"full", 4}));
}

FixedSizeString createTemporary(const char* str, size_t length) {
    FixedSizeString tmp{length};
    for(size_t i = 0; i < length; ++i) {
        tmp << str[i];    }
    return std::move(tmp);
}

TEST(FixedSizeString, moveSemantics) {
    FixedSizeString moveString{createTemporary("move semantics", 14)};
    EXPECT_EQ(moveString.length(), 14);
    EXPECT_EQ(moveString, (ConstString{"move semantics", 14})) << moveString.cString();
    moveString = createTemporary("move assigment!", 15);
    EXPECT_EQ(moveString.length(), 15);
    EXPECT_EQ(moveString, (ConstString{"move assigment!", 15}));
}