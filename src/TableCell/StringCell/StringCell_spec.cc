#include "StringCell.h"
#include "gtest/gtest.h"
#include "../../It/It.h"

TEST(StringCell, getValueAsNumber) {
    IT("constantly return Number instance with Value integer 0");
    FixedSizeString str{3};
    str << 'i' << 'v' << 'o';
    EXPECT_EQ(StringCell{std::move(str)}.getValueAsNumber().getInteger(), 0);
    FixedSizeString str2{0};
    EXPECT_EQ(StringCell{std::move(str2)}.getValueAsNumber().getInteger(), 0);
    FixedSizeString str3{1};
    str3 << 'i';
    EXPECT_EQ(StringCell{std::move(str3)}.getValueAsNumber().getInteger(), 0);
}

TEST(StringCell, calculateOutputLength) {
    IT("returns the same number as the string value's length");
    FixedSizeString str1{9};
    str1 << 's' << 'o' << 'm' << 'e' << ' ' << 't' << 'e' << 'x' << 't';
    EXPECT_EQ(StringCell{std::move(str1)}.calculateOutputLength(), 9);
    FixedSizeString str2{4};
    str2 << '@' << '#' << '$' << '%';
    EXPECT_EQ(StringCell{std::move(str2)}.calculateOutputLength(), 4);
    FixedSizeString str3{12};
    str3 << 'H' << 'e' << 'l' << 'l' << 'o' << ' ' << 'w' << 'o' << 'r' << 'l' << 'd' << '!';
    EXPECT_EQ(StringCell{std::move(str3)}.calculateOutputLength(), 12);
    FixedSizeString str4{4};
    str4 << 'a' << '\\' << 's' << 'd';
    EXPECT_EQ(StringCell{std::move(str4)}.calculateOutputLength(), 4);
    FixedSizeString str5{6};
    str5 << '1' << '\\' << '2' << '"' << '3' << '\\';
    EXPECT_EQ(StringCell{std::move(str5)}.calculateOutputLength(), 6);
    FixedSizeString str6{6};
    str6 << '|' << '\\' << '\"' << '\\' << '"' << '|';
    EXPECT_EQ(StringCell{std::move(str6)}.calculateOutputLength(), 6);
    FixedSizeString str7{7};
    str7 << '"' << 'q' << 'u' << 'o' << 't' << 'e' << '"';
    EXPECT_EQ(StringCell{std::move(str7)}.calculateOutputLength(), 7);
    FixedSizeString str8{16};
    str8 << 'e' << '\\' << '"' << 's' << '\\' << 'c' << '"' << 'a' << 'p' << 'e' << '\\' << '\\' << '\\' << 'i' << 't' << '!';
    EXPECT_EQ(StringCell{std::move(str8)}.calculateOutputLength(), 16);
}

TEST(StringCell, calculateSerializedLength) {
    IT("returns the same number as the string value's length");
    FixedSizeString str1{9};
    str1 << 's' << 'o' << 'm' << 'e' << ' ' << 't' << 'e' << 'x' << 't';
    EXPECT_EQ(StringCell{std::move(str1)}.calculateSerializedLength(), 11);
    FixedSizeString str2{4};
    str2 << '@' << '#' << '$' << '%';
    EXPECT_EQ(StringCell{std::move(str2)}.calculateSerializedLength(), 6);
    FixedSizeString str3{12};
    str3 << 'H' << 'e' << 'l' << 'l' << 'o' << ' ' << 'w' << 'o' << 'r' << 'l' << 'd' << '!';
    EXPECT_EQ(StringCell{std::move(str3)}.calculateSerializedLength(), 14);
    FixedSizeString str4{4};
    str4 << 'a' << '\\' << 's' << 'd';
    EXPECT_EQ(StringCell{std::move(str4)}.calculateSerializedLength(), 7);
    FixedSizeString str5{6};
    str5 << '1' << '\\' << '2' << '"' << '3' << '\\';
    EXPECT_EQ(StringCell{std::move(str5)}.calculateSerializedLength(), 11);
    FixedSizeString str6{6};
    str6 << '|' << '\\' << '"' << '\\' << '"' << '|';
    EXPECT_EQ(StringCell{std::move(str6)}.calculateSerializedLength(), 12);
    FixedSizeString str7{7};
    str7 << '"' << 'q' << 'u' << 'o' << 't' << 'e' << '"';
    EXPECT_EQ(StringCell{std::move(str7)}.calculateSerializedLength(), 11);
    FixedSizeString str8{16};
    str8 << 'e' << '\\' << '"' << 's' << '\\' << 'c' << '"' << 'a' << 'p' << 'e' << '\\' << '\\' << '\\' << 'i' << 't' << '!';
    EXPECT_EQ(StringCell{std::move(str8)}.calculateSerializedLength(), 25);
}