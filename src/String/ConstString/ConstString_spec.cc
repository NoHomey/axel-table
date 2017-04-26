#include "ConstString.h"
#include "gtest/gtest.h"
#include "../../It/It.h"

TEST(ConstString, isNull) {
    IT("should return true if string internally is nullptr");
    ConstString str;
    EXPECT_TRUE(str.isNull());
    EXPECT_TRUE(ConstString().isNull());

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
    EXPECT_FALSE(ConstString().isEmpty());
    EXPECT_FALSE(ConstString("0").isEmpty());

    ConstString str2 = {"1234.56789"};
    EXPECT_FALSE(str2.isEmpty());

    ConstString str3 = {""};
    EXPECT_TRUE(str3.isEmpty());
    EXPECT_TRUE(ConstString("\0").isEmpty());
    EXPECT_TRUE(ConstString("\0sfdsda").isEmpty());

    ConstString str4 = {"This is a \"ConstString\"!"};
    EXPECT_FALSE(str4.isEmpty());
}

TEST(ConstString, hasContent) {
    IT("should return true if string is not Empty or Null");
    ConstString str;
    EXPECT_FALSE(str.hasContent());
    EXPECT_FALSE(ConstString().hasContent());
    EXPECT_FALSE(ConstString("").hasContent());
    EXPECT_TRUE(ConstString("0").hasContent());

    ConstString str2 = {"1234.56789"};
    EXPECT_TRUE(str2.hasContent());

    ConstString str3 = {""};
    EXPECT_FALSE(str3.hasContent());
    EXPECT_FALSE(ConstString("\0").hasContent());
    EXPECT_FALSE(ConstString("\0sfdsda").hasContent());

    ConstString str4 = {"This is a \"ConstString\"!"};
    EXPECT_TRUE(str4.hasContent());
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
}

TEST(ConstString, cString) {
    IT("should return a non-modifiable standard C character array version of the string");
    ConstString str;
    EXPECT_EQ(str.cString(), nullptr);

    const char* data = "1234.56789";
    ConstString str2 = {data};
    EXPECT_EQ(str2.cString(), data);
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
}

TEST(ConstString, equalityOperators) {
    IT("should compare dose two strings have equal value");
    ConstString str = {"some text"};
    EXPECT_EQ(str, str);
    EXPECT_EQ(ConstString("1234.56789"), ConstString("1234.56789"));
    EXPECT_EQ(ConstString(), ConstString());
    EXPECT_EQ(ConstString(""), ConstString(""));
    EXPECT_EQ(ConstString("text"), ConstString("text"));
    EXPECT_EQ(ConstString("Verry verry long text :)"), ConstString("Verry verry long text :)"));
    EXPECT_EQ(ConstString(""), ConstString());
    EXPECT_NE(ConstString("text"), ConstString("txt"));
    EXPECT_NE(ConstString(""), ConstString("0"));
    EXPECT_NE(ConstString(), ConstString("0"));
    EXPECT_NE(ConstString("12345"), ConstString("123.45"));
    EXPECT_NE(ConstString("txt"), ConstString("text"));
    EXPECT_NE(ConstString("-235435"), ConstString("+235435"));
    EXPECT_FALSE(str != str);
}

TEST(ConstString, lessThanOperator) {
    IT("should compare two StringObjects lexicographically,  check is right bigger");
    ConstString str = {"some text"};
    EXPECT_FALSE(str < str);
    EXPECT_FALSE(ConstString() < ConstString(""));
    EXPECT_FALSE(ConstString("") < ConstString());
    EXPECT_FALSE(ConstString("0") < ConstString(""));
    EXPECT_FALSE(ConstString("abcdz") < ConstString("abcde"));
    EXPECT_FALSE(ConstString("12934.56") < ConstString("12234.560"));
    EXPECT_FALSE(ConstString("999512") < ConstString("99921"));
    EXPECT_FALSE(ConstString("1.23") < ConstString("1.23"));
    EXPECT_FALSE(ConstString("tyxt") < ConstString("txt"));
    EXPECT_TRUE(ConstString() < ConstString("0"));
    EXPECT_TRUE(ConstString("abcd") < ConstString("abcde"));
    EXPECT_TRUE(ConstString("12234.56") < ConstString("12234.560"));
    EXPECT_TRUE(ConstString("99912") < ConstString("99921"));
    EXPECT_TRUE(ConstString("0.23") < ConstString("1.23"));
    EXPECT_TRUE(ConstString("text") < ConstString("txt"));
}

TEST(ConstString, greaterThanOperator) {
    IT("should compare two StringObjects lexicographically, check is left bigger");
    ConstString str = {"some text"};
    EXPECT_FALSE(str > str);
    EXPECT_FALSE(ConstString() > ConstString(""));
    EXPECT_FALSE(ConstString("") > ConstString());
    EXPECT_FALSE(ConstString() > ConstString("0"));
    EXPECT_FALSE(ConstString("abcd") > ConstString("abcde"));
    EXPECT_FALSE(ConstString("12234.56") > ConstString("12234.560"));
    EXPECT_FALSE(ConstString("99912") > ConstString("99921"));
    EXPECT_FALSE(ConstString("0.23") > ConstString("1.23"));
    EXPECT_FALSE(ConstString("1.23") > ConstString("1.23"));
    EXPECT_FALSE(ConstString("text") > ConstString("txt"));
    EXPECT_TRUE(ConstString("0") > ConstString(""));
    EXPECT_TRUE(ConstString("abcdz") > ConstString("abcde"));
    EXPECT_TRUE(ConstString("12934.56") > ConstString("12234.560"));
    EXPECT_TRUE(ConstString("999512") > ConstString("99921"));
    EXPECT_TRUE(ConstString("tyxt") > ConstString("txt"));
}