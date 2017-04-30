#include "ConstString.h"
#include "gtest/gtest.h"
#include "../../It/It.h"

TEST(ConstString, throwingBadStringOffset) {
    IT("should throw BadStringOffset if offset constructor is used and offset is bigger than length");
    ConstString str;
    EXPECT_THROW((ConstString{str, 2}), ConstString::BadStringOffset);
    EXPECT_THROW((ConstString{str, 1, true}), ConstString::BadStringOffset);
    EXPECT_NO_THROW((ConstString{str, 0}));
    EXPECT_NO_THROW((ConstString{str, 0, true}));
    ConstString str2 = {"some text"};
    EXPECT_THROW((ConstString{str2, 10}), ConstString::BadStringOffset);
    EXPECT_THROW((ConstString{str2, 10, true}), ConstString::BadStringOffset);
    EXPECT_NO_THROW((ConstString{str2, 3}));
    EXPECT_NO_THROW((ConstString{str2, 3, true}));
}

TEST(ConstString, isNull) {
    IT("should return true if string internally is nullptr");
    ConstString str;
    EXPECT_TRUE(str.isNull());
    EXPECT_TRUE(ConstString{}.isNull());

    ConstString str2 = {"1234.56789"};
    EXPECT_FALSE(str2.isNull());

    ConstString str3 = {""};
    EXPECT_FALSE(str3.isNull());

    ConstString str4 = {"This is a \"ConstString\"!"};
    EXPECT_FALSE(str4.isNull());
}

TEST(ConstString, isEmpty) {
    IT("should return true if string is a empty string");
    ConstString str;
    EXPECT_FALSE(str.isEmpty());
    EXPECT_FALSE(ConstString{}.isEmpty());
    EXPECT_FALSE(ConstString{"0"}.isEmpty());

    ConstString str2 = {"1234.56789"};
    EXPECT_FALSE(str2.isEmpty());

    ConstString str3 = {""};
    EXPECT_TRUE(str3.isEmpty());
    EXPECT_TRUE(ConstString{"\0"}.isEmpty());
    EXPECT_TRUE(ConstString{"\0sfdsda"}.isEmpty());

    ConstString str4 = {"This is a \"ConstString\"!"};
    EXPECT_FALSE(str4.isEmpty());

    ConstString str5 = {",", 1, true};
    EXPECT_TRUE(str5.isEmpty());

    ConstString str6 = {str2, 10};
    EXPECT_TRUE(str6.isEmpty());

    ConstString str7 = {"avcbc", 2, true};
    EXPECT_FALSE(str7.isEmpty());

    ConstString str8 = {str7, 2};
    EXPECT_FALSE(str8.isEmpty());
}

TEST(ConstString, hasContent) {
    IT("should return true if string is not Empty or Null");
    ConstString str;
    EXPECT_FALSE(str.hasContent());
    EXPECT_FALSE(ConstString{}.hasContent());
    EXPECT_FALSE(ConstString{""}.hasContent());
    EXPECT_TRUE(ConstString{"0"}.hasContent());

    ConstString str2 = {"1234.56789"};
    EXPECT_TRUE(str2.hasContent());

    ConstString str3 = {""};
    EXPECT_FALSE(str3.hasContent());
    EXPECT_FALSE(ConstString{"\0"}.hasContent());
    EXPECT_FALSE(ConstString{"\0sfdsda"}.hasContent());

    ConstString str4 = {"This is a \"ConstString\"!"};
    EXPECT_TRUE(str4.hasContent());

    ConstString str5 = {",", 1, true};
    EXPECT_FALSE(str5.hasContent());

    ConstString str6 = {str2, 10};
    EXPECT_FALSE(str6.hasContent());

    ConstString str7 = {"avcbc", 2, true};
    EXPECT_TRUE(str7.hasContent());

    ConstString str8 = {str7, 2};
    EXPECT_TRUE(str8.hasContent());
}

TEST(ConstString, length) {
    IT("should return the number of chars before \\0");
    ConstString str;
    EXPECT_EQ(str.length(), 0);

    ConstString str2 = {"1234.56789"};
    EXPECT_EQ(str2.length(), 10);

    ConstString str3 = {""};
    EXPECT_EQ(str3.length(), 0);

    ConstString str4 = {"This is a \"ConstString\"!"};
    EXPECT_EQ(str4.length(), 24);

    ConstString str5 = {"549589358935"};
    EXPECT_EQ(str5.length(), 12);

    ConstString str6 = {"123a4", 2, true};
    EXPECT_EQ(str6.length(), 3);

    ConstString str7 = {"123.234\"  ", 3, true};
    EXPECT_EQ(str7.length(), 7);

    ConstString str8 = {str7, 3};
    EXPECT_EQ(str8.length(), 4);

    ConstString str9 = {str6, 1};
    EXPECT_EQ(str9.length(), 2);
}

TEST(ConstString, cString) {
    IT("should return a non-modifiable standard C character array version of the string");
    ConstString str;
    EXPECT_EQ(str.cString(), nullptr);

    const char* data = "1234.56789";
    ConstString str2 = {data};
    EXPECT_EQ(str2.cString(), data);

    ConstString str3 = {str2, 3};
    EXPECT_EQ(str3.cString(), data + 3);

    ConstString str4 = {str2, 4};
    EXPECT_EQ(str4.cString(), data + 4);

    ConstString str5 = {str2, 1, true};
    EXPECT_EQ(str5.cString(), data);
}

TEST(ConstString, indexOperator) {
    IT("should return char at the given position or \0 if index is out of range");
    ConstString str;
    EXPECT_TRUE(str.isNull());
    EXPECT_EQ(str[0], '\0');
    EXPECT_EQ(str[9], '\0');

    const char* data = "1234.56789";
    ConstString str2 = {data};
    for(size_t i = 0; data[i] != '\0'; ++i) {
        EXPECT_EQ(str2[i], data[i]);
    }
    EXPECT_EQ(str2[10], '\0');
    EXPECT_EQ(str2[100], '\0');

    ConstString str3 = {"123.234\"  ", 3, true};
    EXPECT_EQ(str3[3], '.');
    EXPECT_EQ(str3[6], '4');
    EXPECT_EQ(str3[7], '\0');

    ConstString str4 = {"123.2347,    ", 5, true};
    EXPECT_EQ(str4[8], '\0');

    ConstString str5 = {str4, 2};
    EXPECT_EQ(str5[0], '3');
    EXPECT_EQ(str5[1], '.');
    EXPECT_EQ(str5[4], '4');
    EXPECT_EQ(str5[5], '7');
    EXPECT_EQ(str5[6], '\0');

    ConstString str6 = {str4, 4};
    EXPECT_EQ(str6[0], '2');
    EXPECT_EQ(str6[1], '3');
    EXPECT_EQ(str6[3], '7');
    EXPECT_EQ(str6[4], '\0');
}

TEST(ConstString, equalityOperators) {
    IT("should compare dose two strings have equal value");
    ConstString str = {"some text"};
    EXPECT_EQ(str, str);
    EXPECT_EQ(ConstString{"1234.56789"}, ConstString{"1234.56789"});
    EXPECT_EQ(ConstString{}, ConstString{});
    EXPECT_EQ(ConstString{""}, ConstString{""});
    EXPECT_EQ(ConstString{"text"}, ConstString{"text"});
    EXPECT_EQ(ConstString{"Verry verry long text :)"}, ConstString{"Verry verry long text :)"});
    EXPECT_EQ(ConstString{""}, ConstString{});
    EXPECT_NE(ConstString{"text"}, ConstString{"txt"});
    EXPECT_NE(ConstString{""}, ConstString{"0"});
    EXPECT_NE(ConstString{}, ConstString{"0"});
    EXPECT_NE(ConstString{"12345"}, ConstString{"123.45"});
    EXPECT_NE(ConstString{"txt"}, ConstString{"text"});
    EXPECT_NE(ConstString{"-235435"}, ConstString{"+235435"});
    EXPECT_FALSE(str != str);

    bool equal = ConstString{str, 5, true} == ConstString{"some"};
    EXPECT_TRUE(equal);
    equal = ConstString{str, 4, true} == ConstString{"some "};
    EXPECT_TRUE(equal);
    equal = ConstString{str, 5} == ConstString{"text"};
    EXPECT_TRUE(equal);
    equal = ConstString{str, 4} == ConstString{" text"};
    EXPECT_TRUE(equal);
}

TEST(ConstString, lessThanOperator) {
    IT("should compare two StringObjects lexicographically,  check is right bigger");
    ConstString str = {"some text"};
    EXPECT_FALSE(str < str);
    EXPECT_FALSE(ConstString{} < ConstString{""});
    EXPECT_FALSE(ConstString{""} < ConstString{});
    EXPECT_FALSE(ConstString{"0"} < ConstString{""});
    EXPECT_FALSE(ConstString{"abcdz"} < ConstString{"abcde"});
    EXPECT_FALSE(ConstString{"12934.56"} < ConstString{"12234.560"});
    EXPECT_FALSE(ConstString{"999512"} < ConstString{"99921"});
    EXPECT_FALSE(ConstString{"1.23"} < ConstString{"1.23"});
    EXPECT_FALSE(ConstString{"tyxt"} < ConstString{"txt"});
    EXPECT_TRUE(ConstString{} < ConstString{"0"});
    EXPECT_TRUE(ConstString{"abcd"} < ConstString{"abcde"});
    EXPECT_TRUE(ConstString{"12234.56"} < ConstString{"12234.560"});
    EXPECT_TRUE(ConstString{"99912"} < ConstString{"99921"});
    EXPECT_TRUE(ConstString{"0.23"} < ConstString{"1.23"});
    EXPECT_TRUE(ConstString{"text"} < ConstString{"txt"});
}

TEST(ConstString, greaterThanOperator) {
    IT("should compare two StringObjects lexicographically, check is left bigger");
    ConstString str = {"some text"};
    EXPECT_FALSE(str > str);
    EXPECT_FALSE(ConstString{} > ConstString{""});
    EXPECT_FALSE(ConstString{""} > ConstString{});
    EXPECT_FALSE(ConstString{} > ConstString{"0"});
    EXPECT_FALSE(ConstString{"abcd"} > ConstString{"abcde"});
    EXPECT_FALSE(ConstString{"12234.56"} > ConstString{"12234.560"});
    EXPECT_FALSE(ConstString{"99912"} > ConstString{"99921"});
    EXPECT_FALSE(ConstString{"0.23"} > ConstString{"1.23"});
    EXPECT_FALSE(ConstString{"1.23"} > ConstString{"1.23"});
    EXPECT_FALSE(ConstString{"text"} > ConstString{"txt"});
    EXPECT_TRUE(ConstString{"0"} > ConstString{""});
    EXPECT_TRUE(ConstString{"abcdz"} > ConstString{"abcde"});
    EXPECT_TRUE(ConstString{"12934.56"} > ConstString{"12234.560"});
    EXPECT_TRUE(ConstString{"999512"} > ConstString{"99921"});
    EXPECT_TRUE(ConstString{"tyxt"} > ConstString{"txt"});
}