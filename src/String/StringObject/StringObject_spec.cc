#include "StringObject.h"
#include "gtest/gtest.h"
#include "../../It/It.h"

TEST(StringObject, isNull) {
    IT("should return true if string internally is nullptr");
    StringObject str;
    EXPECT_TRUE(str.isNull());
    EXPECT_TRUE(StringObject().isNull());

    StringObject str2 = {"1234.56789"};
    EXPECT_FALSE(str2.isNull());

    StringObject str3 = {""};
    EXPECT_FALSE(str3.isNull());

    StringObject str4 = {"This is a \"StringObject\"!"};
    EXPECT_FALSE(str4.isNull());
}

TEST(StringObject, isEmpty) {
    IT("should return true if string is a empty string");
    StringObject str;
    EXPECT_FALSE(str.isEmpty());
    EXPECT_FALSE(StringObject().isEmpty());
    EXPECT_FALSE(StringObject("0").isEmpty());

    StringObject str2 = {"1234.56789"};
    EXPECT_FALSE(str2.isEmpty());

    StringObject str3 = {""};
    EXPECT_TRUE(str3.isEmpty());
    EXPECT_TRUE(StringObject("\0").isEmpty());
    EXPECT_TRUE(StringObject("\0sfdsda").isEmpty());

    StringObject str4 = {"This is a \"StringObject\"!"};
    EXPECT_FALSE(str4.isEmpty());
}

TEST(StringObject, hasContent) {
    IT("should return true if string is not Empty or Null");
    StringObject str;
    EXPECT_FALSE(str.hasContent());
    EXPECT_FALSE(StringObject().hasContent());
    EXPECT_FALSE(StringObject("").hasContent());
    EXPECT_TRUE(StringObject("0").hasContent());

    StringObject str2 = {"1234.56789"};
    EXPECT_TRUE(str2.hasContent());

    StringObject str3 = {""};
    EXPECT_FALSE(str3.hasContent());
    EXPECT_FALSE(StringObject("\0").hasContent());
    EXPECT_FALSE(StringObject("\0sfdsda").hasContent());

    StringObject str4 = {"This is a \"StringObject\"!"};
    EXPECT_TRUE(str4.hasContent());
}

TEST(StringObject, length) {
    IT("should return the number of chars before \\0");
    StringObject str;
    EXPECT_EQ(str.length(), 0);

    StringObject str2 = {"1234.56789"};
    EXPECT_EQ(str2.length(), 10);

    StringObject str3 = {""};
    EXPECT_EQ(str3.length(), 0);

    StringObject str4 = {"This is a \"StringObject\"!"};
    EXPECT_EQ(str4.length(), 25);

    StringObject str5 = {"549589358935"};
    EXPECT_EQ(str5.length(), 12);
}

TEST(StringObject, cString) {
    IT("should return a non-modifiable standard C character array version of the string");
    StringObject str;
    EXPECT_EQ(str.cString(), nullptr);

    const char* data = "1234.56789";
    StringObject str2 = {data};
    EXPECT_EQ(str2.cString(), data);
}

TEST(StringObject, indexOperator) {
    IT("should return char at the given position or \0 if index is out of range");
    StringObject str;
    EXPECT_TRUE(str.isNull());
    EXPECT_EQ(str[0], '\0');
    EXPECT_EQ(str[9], '\0');

    const char* data = "1234.56789";
    StringObject str2 = {data};
    for(size_t i = 0; data[i] != '\0'; ++i) {
        EXPECT_EQ(str2[i], data[i]);
    }
    EXPECT_EQ(str2[10], '\0');
    EXPECT_EQ(str2[100], '\0');
}

TEST(StringObject, equalityOperators) {
    IT("should compare dose two strings have equal value");
    StringObject str = {"some text"};
    EXPECT_EQ(str, str);
    EXPECT_EQ(StringObject("1234.56789"), StringObject("1234.56789"));
    EXPECT_EQ(StringObject(), StringObject());
    EXPECT_EQ(StringObject(""), StringObject(""));
    EXPECT_EQ(StringObject("text"), StringObject("text"));
    EXPECT_EQ(StringObject("Verry verry long text :)"), StringObject("Verry verry long text :)"));
    EXPECT_EQ(StringObject(""), StringObject());
    EXPECT_NE(StringObject("text"), StringObject("txt"));
    EXPECT_NE(StringObject(""), StringObject("0"));
    EXPECT_NE(StringObject(), StringObject("0"));
    EXPECT_NE(StringObject("12345"), StringObject("123.45"));
    EXPECT_NE(StringObject("txt"), StringObject("text"));
    EXPECT_NE(StringObject("-235435"), StringObject("+235435"));
    EXPECT_FALSE(str != str);
}

TEST(StringObject, lessThanOperator) {
    IT("should compare two StringObjects lexicographically,  check is right bigger");
    StringObject str = {"some text"};
    EXPECT_FALSE(str < str);
    EXPECT_FALSE(StringObject() < StringObject(""));
    EXPECT_FALSE(StringObject("") < StringObject());
    EXPECT_FALSE(StringObject("0") < StringObject(""));
    EXPECT_FALSE(StringObject("abcdz") < StringObject("abcde"));
    EXPECT_FALSE(StringObject("12934.56") < StringObject("12234.560"));
    EXPECT_FALSE(StringObject("999512") < StringObject("99921"));
    EXPECT_FALSE(StringObject("1.23") < StringObject("1.23"));
    EXPECT_FALSE(StringObject("tyxt") < StringObject("txt"));
    EXPECT_TRUE(StringObject() < StringObject("0"));
    EXPECT_TRUE(StringObject("abcd") < StringObject("abcde"));
    EXPECT_TRUE(StringObject("12234.56") < StringObject("12234.560"));
    EXPECT_TRUE(StringObject("99912") < StringObject("99921"));
    EXPECT_TRUE(StringObject("0.23") < StringObject("1.23"));
    EXPECT_TRUE(StringObject("text") < StringObject("txt"));
}

TEST(StringObject, greaterThanOperator) {
    IT("should compare two StringObjects lexicographically, check is left bigger");
    StringObject str = {"some text"};
    EXPECT_FALSE(str > str);
    EXPECT_FALSE(StringObject() > StringObject(""));
    EXPECT_FALSE(StringObject("") > StringObject());
    EXPECT_FALSE(StringObject() > StringObject("0"));
    EXPECT_FALSE(StringObject("abcd") > StringObject("abcde"));
    EXPECT_FALSE(StringObject("12234.56") > StringObject("12234.560"));
    EXPECT_FALSE(StringObject("99912") > StringObject("99921"));
    EXPECT_FALSE(StringObject("0.23") > StringObject("1.23"));
    EXPECT_FALSE(StringObject("1.23") > StringObject("1.23"));
    EXPECT_FALSE(StringObject("text") > StringObject("txt"));
    EXPECT_TRUE(StringObject("0") > StringObject(""));
    EXPECT_TRUE(StringObject("abcdz") > StringObject("abcde"));
    EXPECT_TRUE(StringObject("12934.56") > StringObject("12234.560"));
    EXPECT_TRUE(StringObject("999512") > StringObject("99921"));
    EXPECT_TRUE(StringObject("tyxt") > StringObject("txt"));
}