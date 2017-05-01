#include "FixedSizeString.h"

#include "../BasicString/BasicStringSpec.h"

#include "../ConstString/ConstString.h"

TEST(FixedSizeString, throwingBadStringOffset) {
    BasicStringSpec<FixedSizeString>::throwingBadStringOffset();
}

TEST(FixedSizeString, isNull) {
    BasicStringSpec<FixedSizeString>::isNull();
}

TEST(FixedSizeString, isEmpty) {
    BasicStringSpec<FixedSizeString>::isEmpty();
}

TEST(FixedSizeString, hasContent) {
    BasicStringSpec<FixedSizeString>::hasContent();
}

TEST(FixedSizeString, length) {
    BasicStringSpec<FixedSizeString>::length();
    FixedSizeString str{9};
    EXPECT_EQ(str.length(), 9);
    FixedSizeString str2{14};
    EXPECT_EQ(str2.length(), 14);
}

TEST(FixedSizeString, cString) {
    BasicStringSpec<FixedSizeString>::cString();
}

TEST(FixedSizeString, indexOperator) {
    BasicStringSpec<FixedSizeString>::indexOperator();
}

TEST(FixedSizeString, equalityOperators) {
    BasicStringSpec<FixedSizeString>::equalityOperators();
}

TEST(FixedSizeString, lessThanOperator) {
    BasicStringSpec<FixedSizeString>::lessThanOperator();
}

TEST(FixedSizeString, greaterThanOperator) {
    BasicStringSpec<FixedSizeString>::greaterThanOperator();
}

TEST(FixedSizeString, filling) {
    FixedSizeString ivo{3};
    ivo << 'i' << 'v' << 'o';
    EXPECT_TRUE(ivo == ConstString{"ivo"});
    FixedSizeString str{8};
    str << "fixedStr";
    EXPECT_TRUE(str == ConstString{"fixedStr"});
    FixedSizeString str2{13};
    str2 << "mixed " << 's' << 't' << 'r' << "!!!" << '.';
    EXPECT_TRUE(str2 == ConstString{"mixed str!!!."});
    FixedSizeString full{4};
    full << "full" << 'y' << ' ' << "str" << "!!" << '!';
    EXPECT_TRUE(full == ConstString{"full"});
}

FixedSizeString createTemporary(const char* str) {
    FixedSizeString tmp{ConstString{str}.length()};
    tmp << str;
    return std::move(tmp);
}

TEST(FixedSizeString, moveSemantics) {
    FixedSizeString moveString{createTemporary("move semantics")};
    EXPECT_EQ(moveString.length(), 14);
    EXPECT_EQ(moveString, ConstString{"move semantics"});
    moveString = createTemporary("move assigment!");
    EXPECT_EQ(moveString.length(), 15);
    EXPECT_EQ(moveString, ConstString{"move assigment!"});
}