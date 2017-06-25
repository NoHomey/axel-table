#include "DynamicString.h"
#include "gtest/gtest.h"
#include "../../It/It.h"
#include "../ConstString/ConstString.h"

class DynamicStringTest: public ::testing::Test {
public:
    DynamicStringTest() noexcept
    : str{},
    str1{"Hellow world!"},
    str2{"Some text"},
    str3{"This Escalated quickly."},
    str4{"This is a test case"},
    str5{"Git commit, Git push, wait for it ..., save your life! floor is code"},
    str6{"Creativity"},
    str7{"Placeholder"},
    str8{"In development"},
    str9{"12:54, Sunday 25.06.2017"},
    str10{"\0"},
    str11{nullptr} { }

protected:
    DynamicString str;
    DynamicString str1;
    DynamicString str2;
    DynamicString str3;
    DynamicString str4;
    DynamicString str5;
    DynamicString str6;
    DynamicString str7;
    DynamicString str8;
    DynamicString str9;
    DynamicString str10;
    DynamicString str11;
};

TEST_F(DynamicStringTest, DefaultConstructor) {
    IT("should create an empty string");

    EXPECT_TRUE(str.isEmpty());
    EXPECT_EQ(str.length(), 0);
}

TEST_F(DynamicStringTest, isEmpty) {
    IT("should return true if string is empty (eg. it has 0 length)");

    EXPECT_TRUE(str.isEmpty());
    EXPECT_FALSE(str1.isEmpty());
    EXPECT_FALSE(str2.isEmpty());
    EXPECT_FALSE(str3.isEmpty());
    EXPECT_FALSE(str4.isEmpty());
    EXPECT_FALSE(str5.isEmpty());
    EXPECT_FALSE(str6.isEmpty());
    EXPECT_FALSE(str7.isEmpty());
    EXPECT_FALSE(str8.isEmpty());
    EXPECT_FALSE(str9.isEmpty());
    EXPECT_TRUE(str10.isEmpty());
    EXPECT_TRUE(str11.isEmpty());
}

TEST_F(DynamicStringTest, length) {
    IT("returns the length of the string");

    EXPECT_EQ(str.length(), 0);
    EXPECT_EQ(str1.length(), 13);
    EXPECT_EQ(str2.length(), 9);
    EXPECT_EQ(str3.length(), 23);
    EXPECT_EQ(str4.length(), 19);
    EXPECT_EQ(str5.length(), 68);
    EXPECT_EQ(str6.length(), 10);
    EXPECT_EQ(str7.length(), 11);
    EXPECT_EQ(str8.length(), 14);
    EXPECT_EQ(str9.length(), 24);
    EXPECT_EQ(str10.length(), 0);
    EXPECT_EQ(str11.length(), 0);
}

TEST_F(DynamicStringTest, capacity) {
    IT("returns the number of characters that the string has currently allocated space for");

    EXPECT_EQ(str.capacity(), 0);
    EXPECT_EQ(str1.capacity(), 13);
    EXPECT_EQ(str2.capacity(), 9);
    EXPECT_EQ(str3.capacity(), 23);
    EXPECT_EQ(str4.capacity(), 19);
    EXPECT_EQ(str5.capacity(), 68);
    EXPECT_EQ(str6.capacity(), 10);
    EXPECT_EQ(str7.capacity(), 11);
    EXPECT_EQ(str8.capacity(), 14);
    EXPECT_EQ(str9.capacity(), 24);
    EXPECT_EQ(str10.capacity(), 0);
    EXPECT_EQ(str11.capacity(), 0);
}

TEST_F(DynamicStringTest, cStringWhenEmpty) {
    IT("should return nullptr");

    EXPECT_EQ(str.cString(), nullptr);
    EXPECT_EQ(str10.cString(), nullptr);
    EXPECT_EQ(str11.cString(), nullptr);
}


TEST_F(DynamicStringTest, cStringAndIndexOperator) {
    IT("should return nullptr");

    {
        const char* data = str.cString();
        EXPECT_EQ(data, nullptr);
        EXPECT_EQ(str[0], '\0');
        EXPECT_EQ(str[1], '\0');
        EXPECT_EQ(str[2], '\0');
        EXPECT_EQ(str[10], '\0');
        EXPECT_EQ(str[20], '\0');
    }

    {
        const char* data = str1.cString();
        EXPECT_NE(data, nullptr);
        EXPECT_EQ(str1[0], 'H'); EXPECT_EQ(data[0], 'H');
        EXPECT_EQ(str1[1], 'e'); EXPECT_EQ(data[1], 'e');
        EXPECT_EQ(str1[2], 'l'); EXPECT_EQ(data[2], 'l');
        EXPECT_EQ(str1[3], 'l'); EXPECT_EQ(data[3], 'l');
        EXPECT_EQ(str1[4], 'o'); EXPECT_EQ(data[4], 'o');
        EXPECT_EQ(str1[5], 'w'); EXPECT_EQ(data[5], 'w');
        EXPECT_EQ(str1[6], ' '); EXPECT_EQ(data[6], ' ');
        EXPECT_EQ(str1[7], 'w'); EXPECT_EQ(data[7], 'w');
        EXPECT_EQ(str1[8], 'o'); EXPECT_EQ(data[8], 'o');
        EXPECT_EQ(str1[9], 'r'); EXPECT_EQ(data[9], 'r');
        EXPECT_EQ(str1[10], 'l'); EXPECT_EQ(data[10], 'l');
        EXPECT_EQ(str1[11], 'd'); EXPECT_EQ(data[11], 'd');
        EXPECT_EQ(str1[12], '!'); EXPECT_EQ(data[12], '!');
        EXPECT_EQ(str1[13], '\0'); EXPECT_EQ(data[13], '\0');
    }

    {
        const char* data = str2.cString();
        EXPECT_NE(data, nullptr);
        EXPECT_EQ(str2[0], 'S'); EXPECT_EQ(data[0], 'S');
        EXPECT_EQ(str2[1], 'o'); EXPECT_EQ(data[1], 'o');
        EXPECT_EQ(str2[2], 'm'); EXPECT_EQ(data[2], 'm');
        EXPECT_EQ(str2[3], 'e'); EXPECT_EQ(data[3], 'e');
        EXPECT_EQ(str2[4], ' '); EXPECT_EQ(data[4], ' ');
        EXPECT_EQ(str2[5], 't'); EXPECT_EQ(data[5], 't');
        EXPECT_EQ(str2[6], 'e'); EXPECT_EQ(data[6], 'e');
        EXPECT_EQ(str2[7], 'x'); EXPECT_EQ(data[7], 'x');
        EXPECT_EQ(str2[8], 't'); EXPECT_EQ(data[8], 't');
        EXPECT_EQ(str2[9], '\0'); EXPECT_EQ(data[9], '\0');
    }

    {
        const char* data = str6.cString();
        EXPECT_NE(data, nullptr);
        EXPECT_EQ(str6[0], 'C'); EXPECT_EQ(data[0], 'C');
        EXPECT_EQ(str6[1], 'r'); EXPECT_EQ(data[1], 'r');
        EXPECT_EQ(str6[2], 'e'); EXPECT_EQ(data[2], 'e');
        EXPECT_EQ(str6[3], 'a'); EXPECT_EQ(data[3], 'a');
        EXPECT_EQ(str6[4], 't'); EXPECT_EQ(data[4], 't');
        EXPECT_EQ(str6[5], 'i'); EXPECT_EQ(data[5], 'i');
        EXPECT_EQ(str6[6], 'v'); EXPECT_EQ(data[6], 'v');
        EXPECT_EQ(str6[7], 'i'); EXPECT_EQ(data[7], 'i');
        EXPECT_EQ(str6[8], 't'); EXPECT_EQ(data[8], 't');
        EXPECT_EQ(str6[9], 'y'); EXPECT_EQ(data[9], 'y');
        EXPECT_EQ(str6[10], '\0'); EXPECT_EQ(data[10], '\0');
    }

    {
        const char* data = str10.cString();
        EXPECT_EQ(data, nullptr);
        EXPECT_EQ(str10[0], '\0');
        EXPECT_EQ(str10[1], '\0');
        EXPECT_EQ(str10[2], '\0');
        EXPECT_EQ(str10[10], '\0');
        EXPECT_EQ(str10[20], '\0');
    }

    {
        const char* data = str11.cString();
        EXPECT_EQ(data, nullptr);
        EXPECT_EQ(str11[0], '\0');
        EXPECT_EQ(str11[1], '\0');
        EXPECT_EQ(str11[2], '\0');
        EXPECT_EQ(str11[10], '\0');
        EXPECT_EQ(str11[20], '\0');
    }
}

TEST_F(DynamicStringTest, equlityOperators) {
    IT("should compare dose two strings have equal value");

    EXPECT_EQ(str, str);
    EXPECT_EQ(str, DynamicString{});
    EXPECT_EQ(str, (ConstString{"", 0}));

    EXPECT_EQ(str1, str1);
    EXPECT_EQ(str1, DynamicString{"Hellow world!"});
    EXPECT_EQ(str1, (ConstString{"Hellow world!", 13}));
    EXPECT_NE(str1, DynamicString{"Hellow world"});
    EXPECT_NE(str1, (ConstString{"Hellow world", 12}));

    EXPECT_EQ(str2, str2);
    EXPECT_EQ(str2, DynamicString{"Some text"});
    EXPECT_EQ(str2, (ConstString{"Some text", 9}));
    EXPECT_NE(str2, DynamicString{"some text"});
    EXPECT_NE(str2, (ConstString{"some text", 9}));

    EXPECT_EQ(str3, str3);
    EXPECT_EQ(str3, DynamicString{"This Escalated quickly."});
    EXPECT_EQ(str3, (ConstString{"This Escalated quickly.", 23}));
    EXPECT_NE(str3, DynamicString{"This Escalated quickly"});
    EXPECT_NE(str3, (ConstString{"This Escalated quickly", 22}));

    EXPECT_EQ(str4, str4);
    EXPECT_EQ(str4, DynamicString{"This is a test case"});
    EXPECT_EQ(str4, (ConstString{"This is a test case", 19}));
    EXPECT_NE(str4, DynamicString{"That is a test case"});
    EXPECT_NE(str4, (ConstString{"That is a test case", 19}));

    EXPECT_EQ(str5, str5);
    EXPECT_EQ(str5, DynamicString{"Git commit, Git push, wait for it ..., save your life! floor is code"});
    EXPECT_EQ(str5, (ConstString{"Git commit, Git push, wait for it ..., save your life! floor is code", 68}));
    EXPECT_NE(str5, DynamicString{"Git commit, Git push, wait for it ..., save your life! floor is cod3"});
    EXPECT_NE(str5, (ConstString{"Git commit, Git push, wait for it ..., save your life! floor is cod3", 68}));

    EXPECT_EQ(str10, str10);
    EXPECT_EQ(str10, DynamicString{});
    EXPECT_EQ(str10, (ConstString{"\0", 0}));

    EXPECT_EQ(str11, str11);
    EXPECT_EQ(str11, DynamicString{nullptr});
    EXPECT_EQ(str11, (ConstString{nullptr, 0}));
}

TEST(DynamicString, lessThanOperator) {
    IT("should compare two strings lexicographically, checking is right bigger");
    DynamicString str = {"some text"};
    EXPECT_FALSE(str < str);
    EXPECT_FALSE((DynamicString{nullptr}) < (ConstString{"", 0}));
    EXPECT_FALSE((DynamicString{""}) < (ConstString{nullptr, 0}));
    EXPECT_FALSE((DynamicString{"0"}) < (ConstString{"", 0}));
    EXPECT_FALSE((DynamicString{"abcdz"}) < (ConstString{"abcde", 5}));
    EXPECT_FALSE((DynamicString{"12934.56"}) < (ConstString{"12234.560", 8}));
    EXPECT_FALSE((DynamicString{"999512"}) < (ConstString{"99921", 6}));
    EXPECT_FALSE((DynamicString{"1.23"}) < (ConstString{"1.23", 4}));
    EXPECT_FALSE((DynamicString{"tyxt"}) < (ConstString{"txt", 3}));
    EXPECT_TRUE((DynamicString{nullptr}) < (ConstString{"0", 1}));
    EXPECT_TRUE((DynamicString{"abcd"}) < (ConstString{"abcde", 5}));
    EXPECT_TRUE((DynamicString{"12234.56"}) < (ConstString{"12234.560", 9}));
    EXPECT_TRUE((DynamicString{"99912"}) < (ConstString{"99921", 5}));
    EXPECT_TRUE((DynamicString{"0.23"}) < (ConstString{"1.23", 4}));
    EXPECT_TRUE((DynamicString{"text"}) < (ConstString{"txt", 3}));
}

TEST(DynamicString, greaterThanOperator) {
    IT("should compare two strings lexicographically, checking is left bigger");
    DynamicString str = {"some text"};
    EXPECT_FALSE(str > str);
    EXPECT_FALSE((DynamicString{nullptr}) > (ConstString{"", 0}));
    EXPECT_FALSE((DynamicString{""}) > (ConstString{nullptr, 0}));
    EXPECT_FALSE((DynamicString{nullptr}) > (ConstString{"0", 1}));
    EXPECT_FALSE((DynamicString{"abcd"}) > (ConstString{"abcde", 5}));
    EXPECT_FALSE((DynamicString{"12234.56"}) > (ConstString{"12234.560",9}));
    EXPECT_FALSE((DynamicString{"99912"}) > (ConstString{"99921", 5}));
    EXPECT_FALSE((DynamicString{"0.23"}) > (ConstString{"1.23", 4}));
    EXPECT_FALSE((DynamicString{"1.23"}) > (ConstString{"1.23", 4}));
    EXPECT_FALSE((DynamicString{"text"}) > (ConstString{"txt", 3}));
    EXPECT_TRUE((DynamicString{"0"}) > (ConstString{"", 0}));
    EXPECT_TRUE((DynamicString{"abcdz"}) > (ConstString{"abcde", 5}));
    EXPECT_TRUE((DynamicString{"12934.56"}) > (ConstString{"12234.560", 9}));
    EXPECT_TRUE((DynamicString{"999512"}) > (ConstString{"99921", 5}));
    EXPECT_TRUE((DynamicString{"tyxt"}) > (ConstString{"txt", 3}));
}

TEST_F(DynamicStringTest, reserve) {
    IT("reserves storage");

    EXPECT_EQ(str.length(), 0);
    EXPECT_EQ(str.capacity(), 0);
    str.reserve(10);
    EXPECT_EQ(str.length(), 0);
    EXPECT_EQ(str.capacity(), 10);
    str.reserve(22);
    EXPECT_EQ(str.length(), 0);
    EXPECT_EQ(str.capacity(), 32);
    str.reserve(0);
    EXPECT_EQ(str.length(), 0);
    EXPECT_EQ(str.capacity(), 32);

    {
        EXPECT_NE(str.cString(), nullptr);
        EXPECT_EQ(str[0], '\0');
        EXPECT_EQ(str[1], '\0');
        EXPECT_EQ(str[2], '\0');
        EXPECT_EQ(str[10], '\0');
        EXPECT_EQ(str[20], '\0');
    }

    EXPECT_EQ(str5.length(), 68);
    EXPECT_EQ(str5.capacity(), 68);
    str5.reserve(7);
    EXPECT_EQ(str5.length(), 68);
    EXPECT_EQ(str5.capacity(), 75);
    str5.reserve(13);
    EXPECT_EQ(str5.length(), 68);
    EXPECT_EQ(str5.capacity(), 88);
    str5.reserve(0);
    EXPECT_EQ(str5.length(), 68);
    EXPECT_EQ(str5.capacity(), 88);

    EXPECT_EQ(str5, DynamicString{"Git commit, Git push, wait for it ..., save your life! floor is code"});
    EXPECT_EQ(str5, (ConstString{"Git commit, Git push, wait for it ..., save your life! floor is code", 68}));
}

TEST_F(DynamicStringTest, shrinkToFit) {
    IT("releases unused storage by making an allocation and content movement");

    EXPECT_EQ(str.length(), 0);
    EXPECT_EQ(str.capacity(), 0);
    str.shrinkToFit();
    EXPECT_EQ(str.length(), 0);
    EXPECT_EQ(str.capacity(), 0);
    EXPECT_EQ(str.length(), 0);
    EXPECT_EQ(str.capacity(), 0);
    str.reserve(10);
    EXPECT_EQ(str.length(), 0);
    EXPECT_EQ(str.capacity(), 10);
    str.shrinkToFit();
    EXPECT_EQ(str.length(), 0);
    EXPECT_EQ(str.capacity(), 0);
    str.reserve(22);
    EXPECT_EQ(str.length(), 0);
    EXPECT_EQ(str.capacity(), 22);
    str.shrinkToFit();
    EXPECT_EQ(str.length(), 0);
    EXPECT_EQ(str.capacity(), 0);
    str.reserve(0);
    EXPECT_EQ(str.length(), 0);
    EXPECT_EQ(str.capacity(), 0);

    {
        const char* data = str.cString();
        EXPECT_EQ(data, nullptr);
        EXPECT_EQ(str[0], '\0');
        EXPECT_EQ(str[1], '\0');
        EXPECT_EQ(str[2], '\0');
        EXPECT_EQ(str[10], '\0');
        EXPECT_EQ(str[20], '\0');
    }

    EXPECT_EQ(str5.length(), 68);
    EXPECT_EQ(str5.capacity(), 68);
    str5.shrinkToFit();
    EXPECT_EQ(str5.length(), 68);
    EXPECT_EQ(str5.capacity(), 68);
    str5.reserve(7);
    EXPECT_EQ(str5.length(), 68);
    EXPECT_EQ(str5.capacity(), 75);
    str5.shrinkToFit();
    EXPECT_EQ(str5.length(), 68);
    EXPECT_EQ(str5.capacity(), 68);
    str5.reserve(13);
    EXPECT_EQ(str5.length(), 68);
    EXPECT_EQ(str5.capacity(), 81);
    str5.shrinkToFit();
    EXPECT_EQ(str5.length(), 68);
    EXPECT_EQ(str5.capacity(), 68);
    str5.reserve(0);
    EXPECT_EQ(str5.length(), 68);
    EXPECT_EQ(str5.capacity(), 68);
    str5.shrinkToFit();
    EXPECT_EQ(str5.length(), 68);
    EXPECT_EQ(str5.capacity(), 68);

    EXPECT_EQ(str5, DynamicString{"Git commit, Git push, wait for it ..., save your life! floor is code"});
    EXPECT_EQ(str5, (ConstString{"Git commit, Git push, wait for it ..., save your life! floor is code", 68}));
}

TEST_F(DynamicStringTest, clear) {
    IT("releases storage and sets size and capacity to zero");

    EXPECT_TRUE(str.isEmpty());
    EXPECT_EQ(str.length(), 0);
    EXPECT_EQ(str.capacity(), 0);
    EXPECT_EQ(str.cString(), nullptr);

    str.clear();
    EXPECT_TRUE(str.isEmpty());
    EXPECT_EQ(str.length(), 0);
    EXPECT_EQ(str.capacity(), 0);
    EXPECT_EQ(str.cString(), nullptr);

    EXPECT_FALSE(str1.isEmpty());
    EXPECT_EQ(str1.length(), 13);
    EXPECT_EQ(str1.capacity(), 13);
    EXPECT_NE(str1.cString(), nullptr);
    str1.clear();
    EXPECT_TRUE(str1.isEmpty());
    EXPECT_EQ(str1.length(), 0);
    EXPECT_EQ(str1.capacity(), 0);
    EXPECT_EQ(str1.cString(), nullptr);

    EXPECT_FALSE(str2.isEmpty());
    EXPECT_EQ(str2.length(), 9);
    EXPECT_EQ(str2.capacity(), 9);
    EXPECT_NE(str2.cString(), nullptr);
    str2.clear();
    EXPECT_TRUE(str2.isEmpty());
    EXPECT_EQ(str2.length(), 0);
    EXPECT_EQ(str2.capacity(), 0);
    EXPECT_EQ(str2.cString(), nullptr);

    EXPECT_FALSE(str3.isEmpty());
    EXPECT_EQ(str3.length(), 23);
    EXPECT_EQ(str3.capacity(), 23);
    EXPECT_NE(str3.cString(), nullptr);
    str3.clear();
    EXPECT_TRUE(str3.isEmpty());
    EXPECT_EQ(str3.length(), 0);
    EXPECT_EQ(str3.capacity(), 0);
    EXPECT_EQ(str3.cString(), nullptr);

    EXPECT_FALSE(str5.isEmpty());
    EXPECT_EQ(str5.length(), 68);
    EXPECT_EQ(str5.capacity(), 68);
    EXPECT_NE(str5.cString(), nullptr);
    str5.clear();
    EXPECT_TRUE(str5.isEmpty());
    EXPECT_EQ(str5.length(), 0);
    EXPECT_EQ(str5.capacity(), 0);
    EXPECT_EQ(str5.cString(), nullptr);
}