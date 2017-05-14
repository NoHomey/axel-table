#include "ConstString.h"
#include "gtest/gtest.h"
#include "../../It/It.h"

TEST(ConstString, throwingBadStringOffset) {
    IT("should throw BadStringOffset if offset constructor is used and offset is bigger than length");
    ConstString str = {nullptr, 0};
    EXPECT_THROW((ConstString{str, 2}), ConstString::BadStringOffset);
    EXPECT_THROW((ConstString{str, 0, 1}), ConstString::BadStringOffset);
    EXPECT_THROW((ConstString{str, 0}), ConstString::BadStringOffset);
    EXPECT_THROW((ConstString{str, 0, 0}), ConstString::BadStringOffset);
    ConstString str2 = {"some text", 9};
    EXPECT_THROW((ConstString{str2, 10}), ConstString::BadStringOffset);
    EXPECT_THROW((ConstString{str2, 13}), ConstString::BadStringOffset);
    EXPECT_THROW((ConstString{str2, 0, 10}), ConstString::BadStringOffset);
    EXPECT_NO_THROW((ConstString{str2, 3}));
    EXPECT_NO_THROW((ConstString{str2, 0, 3}));

    ConstString str3 = {",", 1};
    EXPECT_THROW((ConstString{str3, 0, 2}), ConstString::BadStringOffset);

    ConstString str4 = {"\0 some text", 11};
    EXPECT_THROW((ConstString{str4, 0, 0}), ConstString::BadStringOffset);
    EXPECT_NO_THROW((ConstString{str4, 1}));
    EXPECT_NO_THROW((ConstString{str4, 0, 1}));
    EXPECT_NO_THROW((ConstString{str4, 1, 1}));
    EXPECT_NO_THROW((ConstString{str4, 0}));
}

TEST(ConstString, isEmpty) {
    IT("should return true if string is a empty string");
    ConstString str = {nullptr, 0};
    EXPECT_TRUE(str.isEmpty());
    EXPECT_TRUE((ConstString{nullptr, 0}).isEmpty());
    EXPECT_FALSE((ConstString{"0", 1}).isEmpty());

    ConstString str2 = {"1234.56789", 10};
    EXPECT_FALSE(str2.isEmpty());

    ConstString str3 = {"", 0};
    EXPECT_TRUE(str3.isEmpty());
    EXPECT_FALSE((ConstString{"\0", 1}).isEmpty());
    EXPECT_FALSE((ConstString{"\0sfdsda", 7}).isEmpty());

    ConstString str4 = {"This is a \"ConstString\"!", 19};
    EXPECT_FALSE(str4.isEmpty());

    ConstString str5 = {"avcbc", 5};
    EXPECT_FALSE((ConstString{str5, 0, 2}).isEmpty());
    EXPECT_FALSE((ConstString{str5, 1, 2}).isEmpty());
    EXPECT_FALSE((ConstString{str5, 4}).isEmpty());
    EXPECT_FALSE((ConstString{str5, 3, 1}).isEmpty());

    ConstString str6 = {str5, 2};
    EXPECT_FALSE(str6.isEmpty());
}

TEST(ConstString, length) {
    IT("should return the number of chars in the string");
    ConstString str = {nullptr, 0};
    EXPECT_EQ(str.length(), 0);

    ConstString str1 = {"\0 1234", 6};
    EXPECT_EQ(str1.length(), 6);

    ConstString str2 = {"1234.56789", 10};
    EXPECT_EQ(str2.length(), 10);

    ConstString str3 = {"", 0};
    EXPECT_EQ(str3.length(), 0);

    ConstString str4 = {"This is a \"ConstString\"!", 19};
    EXPECT_EQ(str4.length(), 19);

    ConstString str5 = {"549589358935", 12};
    EXPECT_EQ(str5.length(), 12);

    ConstString str6 = {{"123a4", 5}, 1, 3};
    EXPECT_EQ(str6.length(), 3);

    ConstString str7 = {{"123.234\"  ", 10}, 2, 7};
    EXPECT_EQ(str7.length(), 7);

    ConstString str8 = {str7, 3};
    EXPECT_EQ(str8.length(), 4);

    ConstString str9 = {str6, 1};
    EXPECT_EQ(str9.length(), 2);

    ConstString str10 = {str5, 0};
    EXPECT_EQ(str10.length(), 12);

    ConstString str11 = {str5, 0, 12};
    EXPECT_EQ(str11.length(), 12);
}

TEST(ConstString, cString) {
    IT("should return a non-modifiable standard C character array version of the string");
    ConstString str = {nullptr, 0};
    EXPECT_EQ(str.cString(), nullptr);
    const char* data = "some text";
    ConstString str1 = {data, 9};
    const char* cString = str1.cString();
    for(size_t i = 0; i < 9; ++i) {
        EXPECT_EQ(cString[i], data[i]);
    }

    const char* data2 = "1234.56789";
    ConstString str2 = {data2, 10};
    EXPECT_EQ(str2.cString(), data2);

    ConstString str3 = {str2, 3};
    EXPECT_EQ(str3.cString(), data2 + 3);

    ConstString str4 = {str2, 4};
    EXPECT_EQ(str4.cString(), data2 + 4);

    ConstString str5 = {str2, 0, 1};
    EXPECT_EQ(str5.cString(), data2);

    ConstString str6 = {str2, 0};
    EXPECT_EQ(str6.cString(), data2);

    ConstString str7 = {str2, 0, 1};
    EXPECT_EQ(str7.cString(), data2);

    ConstString str8 = {str2, 3};
    EXPECT_EQ(str8.cString(), data2 + 3);

    ConstString str9 = {str2, 5, 5};
    EXPECT_EQ(str9.cString(), data2 + 5);
}

TEST(ConstString, indexOperator) {
    IT("should return char at the given position or \\0 if index is out of range");
    ConstString str = {nullptr, 0};
    EXPECT_TRUE(str.isEmpty());
    EXPECT_EQ(str[0], '\0');
    EXPECT_EQ(str[9], '\0');

    const char* data = "1234.56789";
    ConstString str2 = {data, 10};
    for(size_t i = 0; data[i] != '\0'; ++i) {
        EXPECT_EQ(str2[i], data[i]);
    }
    EXPECT_EQ(str2[10], '\0');
    EXPECT_EQ(str2[100], '\0');

    ConstString str3 = {{"123.234\"  ", 10}, 0, 7};
    EXPECT_EQ(str3[3], '.');
    EXPECT_EQ(str3[6], '4');
    EXPECT_EQ(str3[7], '\0');
    ConstString str4 = {{"123.2347,    ", 13}, 2, 6};
    EXPECT_EQ(str4[0], '3');
    EXPECT_EQ(str4[1], '.');
    EXPECT_EQ(str4[4], '4');
    EXPECT_EQ(str4[5], '7');
    EXPECT_EQ(str4[6], '\0');

    ConstString str5 = {str4, 2};
    EXPECT_EQ(str5[1], '3');
    EXPECT_EQ(str5[2], '4');
    EXPECT_EQ(str5[3], '7');
    EXPECT_EQ(str5[4], '\0');

    ConstString str6 = {str4, 4};
    EXPECT_EQ(str6[0], '4');
    EXPECT_EQ(str6[1], '7');
    EXPECT_EQ(str6[2], '\0');
}

TEST(ConstString, equalityOperators) {
    IT("should compare dose two strings have equal value");
    ConstString str = {"some text", 9};
    EXPECT_EQ(str, str);
    EXPECT_EQ((ConstString{"1234.56789", 10}), (ConstString{"1234.56789", 10}));
    EXPECT_EQ((ConstString{nullptr, 0}), (ConstString{nullptr, 0}));
    EXPECT_EQ((ConstString{"", 0}), (ConstString{"", 0}));
    EXPECT_EQ((ConstString{"text", 4}), (ConstString{"text", 4}));
    EXPECT_EQ((ConstString{"Verry verry long text :)", 25}), (ConstString{"Verry verry long text :)", 25}));
    EXPECT_EQ((ConstString{"", 0}), (ConstString{nullptr, 0}));
    EXPECT_FALSE((ConstString{"text", 4}) == (ConstString{"txt", 3}));
    EXPECT_FALSE((ConstString{"", 0}) == (ConstString{"0", 1}));
    EXPECT_FALSE((ConstString{nullptr, 0}) == (ConstString{"0", 1}));
    EXPECT_FALSE((ConstString{"12345", 5}) == (ConstString{"123.45", 6}));
    EXPECT_FALSE((ConstString{"txt", 3}) == (ConstString{"text", 4}));
    EXPECT_FALSE((ConstString{"-235435", 7}) == (ConstString{"+235435", 7}));
    EXPECT_TRUE((ConstString{"text", 4}) != (ConstString{"txt", 3}));
    EXPECT_TRUE((ConstString{"", 0}) != (ConstString{"0", 1}));
    EXPECT_TRUE((ConstString{nullptr, 0}) != (ConstString{"0", 1}));
    EXPECT_TRUE((ConstString{"12345", 5}) != (ConstString{"123.45", 6}));
    EXPECT_TRUE((ConstString{"txt", 3}) != (ConstString{"text", 4}));
    EXPECT_TRUE((ConstString{"-235435", 7}) != (ConstString{"+235435", 7}));
    EXPECT_FALSE(str != str);

    bool equal = ConstString{str, 0, 4} == ConstString{"some", 4};
    EXPECT_TRUE(equal);
    equal = ConstString{str, 0, 5} == ConstString{"some ", 5};
    EXPECT_TRUE(equal);
    equal = ConstString{str, 5} == ConstString{"text", 4};
    EXPECT_TRUE(equal);
    equal = ConstString{str, 4} == ConstString{" text", 5};
    EXPECT_TRUE(equal);
    equal = ConstString{str, 0} == str;
    EXPECT_TRUE(equal);
    equal = ConstString{str, 0, 9} == str;
    EXPECT_TRUE(equal);

    ConstString verryLong = {"Verry verry long text :)", 25};
    EXPECT_EQ((ConstString{verryLong, 6}), (ConstString{"verry long text :)", 19}));
    EXPECT_EQ((ConstString{verryLong, 6, 5}), (ConstString{"verry", 5}));
    EXPECT_EQ((ConstString{verryLong, 12}), (ConstString{"long text :)", 12}));
    EXPECT_EQ((ConstString{verryLong, 12, 9}), (ConstString{"long text", 9}));
    EXPECT_EQ((ConstString{verryLong, 22}), (ConstString{":)", 2}));
    EXPECT_EQ((ConstString{verryLong, 21, 2}), (ConstString{" :", 2}));
    
    EXPECT_NE((ConstString{verryLong, 7}), (ConstString{"verry long text :)", 19}));
    EXPECT_NE((ConstString{verryLong, 6, 4}), (ConstString{"verry", 5}));
    EXPECT_NE((ConstString{verryLong, 11}), (ConstString{"long text :)", 12}));
    EXPECT_NE((ConstString{verryLong, 11, 9}), (ConstString{"long text", 9}));
    EXPECT_NE((ConstString{verryLong, 21}), (ConstString{":)", 2}));
    EXPECT_NE((ConstString{verryLong, 21, 1}), (ConstString{" :", 2}));
}

TEST(ConstString, lessThanOperator) {
    IT("should compare two strings lexicographically, checking is right bigger");
    ConstString str = {"some text", 9};
    EXPECT_FALSE(str < str);
    EXPECT_FALSE((ConstString{nullptr, 0}) < (ConstString{"", 0}));
    EXPECT_FALSE((ConstString{"", 0}) < (ConstString{nullptr, 0}));
    EXPECT_FALSE((ConstString{"0", 1}) < (ConstString{"", 0}));
    EXPECT_FALSE((ConstString{"abcdz", 5}) < (ConstString{"abcde", 5}));
    EXPECT_FALSE((ConstString{"12934.56", 8}) < (ConstString{"12234.560", 8}));
    EXPECT_FALSE((ConstString{"999512", 6}) < (ConstString{"99921", 6}));
    EXPECT_FALSE((ConstString{"1.23", 4}) < (ConstString{"1.23", 4}));
    EXPECT_FALSE((ConstString{"tyxt", 4}) < (ConstString{"txt", 3}));
    EXPECT_TRUE((ConstString{nullptr, 0}) < (ConstString{"0", 1}));
    EXPECT_TRUE((ConstString{"abcd", 4}) < (ConstString{"abcde", 5}));
    EXPECT_TRUE((ConstString{"12234.56", 8}) < (ConstString{"12234.560", 9}));
    EXPECT_TRUE((ConstString{"99912", 5}) < (ConstString{"99921", 5}));
    EXPECT_TRUE((ConstString{"0.23", 4}) < (ConstString{"1.23", 4}));
    EXPECT_TRUE((ConstString{"text", 4}) < (ConstString{"txt", 3}));
}

TEST(ConstString, greaterThanOperator) {
    IT("should compare two strings lexicographically, checking is left bigger");
    ConstString str = {"some text", 9};
    EXPECT_FALSE(str > str);
    EXPECT_FALSE((ConstString{nullptr, 0}) > (ConstString{"", 0}));
    EXPECT_FALSE((ConstString{"", 0}) > (ConstString{nullptr, 0}));
    EXPECT_FALSE((ConstString{nullptr, 0}) > (ConstString{"0", 1}));
    EXPECT_FALSE((ConstString{"abcd", 4}) > (ConstString{"abcde", 5}));
    EXPECT_FALSE((ConstString{"12234.56", 8}) > (ConstString{"12234.560",9}));
    EXPECT_FALSE((ConstString{"99912", 5}) > (ConstString{"99921", 5}));
    EXPECT_FALSE((ConstString{"0.23", 4}) > (ConstString{"1.23", 4}));
    EXPECT_FALSE((ConstString{"1.23", 4}) > (ConstString{"1.23", 4}));
    EXPECT_FALSE((ConstString{"text", 4}) > (ConstString{"txt", 3}));
    EXPECT_TRUE((ConstString{"0", 1}) > (ConstString{"", 0}));
    EXPECT_TRUE((ConstString{"abcdz", 5}) > (ConstString{"abcde", 5}));
    EXPECT_TRUE((ConstString{"12934.56", 8}) > (ConstString{"12234.560", 9}));
    EXPECT_TRUE((ConstString{"999512", 6}) > (ConstString{"99921", 5}));
    EXPECT_TRUE((ConstString{"tyxt", 4}) > (ConstString{"txt", 3}));
}