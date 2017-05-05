#include "BasicString.h"
#include "gtest/gtest.h"
#include "../../It/It.h"

template<typename String>
class BasicStringSpec {
public:
    static void throwingBadStringOffset() noexcept {
        IT("should throw BadStringOffset if offset constructor is used and offset is bigger than length");
        String str = {nullptr, 0};
        EXPECT_THROW((String{str, 2}), BadStringOffset);
        EXPECT_THROW((String{str, 0, 1}), BadStringOffset);
        EXPECT_THROW((String{str, 0}), BadStringOffset);
        EXPECT_THROW((String{str, 0, 0}), BadStringOffset);
        String str2 = {"some text", 9};
        EXPECT_THROW((String{str2, 10}), BadStringOffset);
        EXPECT_THROW((String{str2, 0, 10}), BadStringOffset);
        EXPECT_NO_THROW((String{str2, 3}));
        EXPECT_NO_THROW((String{str2, 0, 3}));

        String str3 = {",", 1};
        EXPECT_THROW((String{str3, 0, 1}), BadStringOffset);

        String str4 = {"\0 some text", 11};
        EXPECT_THROW((String{str4, 1}), BadStringOffset);
        EXPECT_THROW((String{str4, 0, 1}), BadStringOffset);
        EXPECT_THROW((String{str4, 1, 1}), BadStringOffset);
        EXPECT_THROW((String{str4, 0}), BadStringOffset);
        EXPECT_THROW((String{str4, 0, 0}), BadStringOffset);
    }

    static void isNull() noexcept {
        IT("should return true if string internally is nullptr");
        String str = {nullptr, 0};
        EXPECT_TRUE(str.isNull());
        EXPECT_TRUE((String{nullptr, 0}).isNull());

        String str2 = {"1234.56789", 10};
        EXPECT_FALSE(str2.isNull());

        String str3 = {"", 0};
        EXPECT_TRUE(str3.isNull());

        String str4 = {"This is a \"String\"!", 19};
        EXPECT_FALSE(str4.isNull());
    }

    static void isEmpty() noexcept {
        IT("should return true if string is a empty string");
        String str = {nullptr, 0};
        EXPECT_TRUE(str.isEmpty());
        EXPECT_TRUE((String{nullptr, 0}).isEmpty());
        EXPECT_FALSE((String{"0", 1}).isEmpty());

        String str2 = {"1234.56789", 10};
        EXPECT_FALSE(str2.isEmpty());

        String str3 = {"", 0};
        EXPECT_TRUE(str3.isEmpty());
        EXPECT_TRUE((String{"\0", 1}).isEmpty());
        EXPECT_TRUE((String{"\0sfdsda", 7}).isEmpty());

        String str4 = {"This is a \"String\"!", 19};
        EXPECT_FALSE(str4.isEmpty());

        String str5 = {"avcbc", 5};
        EXPECT_FALSE((String{str5, 0, 2}).isEmpty());

        String str6 = {str5, 2};
        EXPECT_FALSE(str6.isEmpty());
    }

    static void hasContent() noexcept {
        IT("should return true if string is not Empty and it is not Null");
        String str = {nullptr, 0};
        EXPECT_FALSE(str.hasContent());
        EXPECT_FALSE((String{nullptr, 0}).hasContent());
        EXPECT_FALSE((String{"", 0}).hasContent());
        EXPECT_TRUE((String{"0", 1}).hasContent());

        String str2 = {"1234.56789", 10};
        EXPECT_TRUE(str2.hasContent());

        String str3 = {"", 0};
        EXPECT_FALSE(str3.hasContent());
        EXPECT_FALSE((String{"\0", 1}).hasContent());
        EXPECT_FALSE((String{"\0sfdsda", 7}).hasContent());

        String str4 = {"This is a \"String\"!", 19};
        EXPECT_TRUE(str4.hasContent());

        String str5 = {"avcbc", 5};
        String str6 = {str5, 0, 2};
        EXPECT_TRUE(str6.hasContent());
        String str7 = {str6, 2};
        EXPECT_TRUE(str7.hasContent());
    }

    static void length() noexcept {
        IT("should return the number of chars in the string");
        String str = {nullptr, 0};
        EXPECT_EQ(str.length(), 0);

        String str1 = {"\0 1234", 6};
        EXPECT_EQ(str1.length(), 0);

        String str2 = {"1234.56789", 10};
        EXPECT_EQ(str2.length(), 10);

        String str3 = {"", 0};
        EXPECT_EQ(str3.length(), 0);

        String str4 = {"This is a \"String\"!", 19};
        EXPECT_EQ(str4.length(), 19);

        String str5 = {"549589358935", 12};
        EXPECT_EQ(str5.length(), 12);

        String str6 = {{"123a4", 5}, 0, 2};
        EXPECT_EQ(str6.length(), 3);

        String str7 = {{"123.234\"  ", 10}, 0, 3};
        EXPECT_EQ(str7.length(), 7);

        String str8 = {str7, 3};
        EXPECT_EQ(str8.length(), 4);

        String str9 = {str6, 1};
        EXPECT_EQ(str9.length(), 2);

        String str10 = {str5, 0};
        EXPECT_EQ(str10.length(), 12);

        String str11 = {str5, 0, 0};
        EXPECT_EQ(str11.length(), 12);
    }

   static void cString() noexcept {
        IT("should return a non-modifiable standard C character array version of the string");
        String str = {nullptr, 0};
        EXPECT_EQ(str.cString(), nullptr);
        const char* data = "some text";
        String str2 = {data, 9};
        const char* cString = str2.cString();
        for(size_t i = 0; i < 9; ++i) {
            EXPECT_EQ(cString[i], data[i]);
        }
    }

    static void indexOperator() noexcept {
        IT("should return char at the given position or \\0 if index is out of range");
        String str = {nullptr, 0};
        EXPECT_TRUE(str.isNull());
        EXPECT_EQ(str[0], '\0');
        EXPECT_EQ(str[9], '\0');

        const char* data = "1234.56789";
        String str2 = {data, 10};
        for(size_t i = 0; data[i] != '\0'; ++i) {
            EXPECT_EQ(str2[i], data[i]);
        }
        EXPECT_EQ(str2[10], '\0');
        EXPECT_EQ(str2[100], '\0');

        String str3 = {{"123.234\"  ", 10}, 0, 3};
        EXPECT_EQ(str3[3], '.');
        EXPECT_EQ(str3[6], '4');
        EXPECT_EQ(str3[7], '\0');
        String str4 = {{"123.2347,    ", 13}, 0, 5};
        EXPECT_EQ(str4[7], '7');
        EXPECT_EQ(str4[8], '\0');

        String str5 = {str4, 2};
        EXPECT_EQ(str5[0], '3');
        EXPECT_EQ(str5[1], '.');
        EXPECT_EQ(str5[4], '4');
        EXPECT_EQ(str5[5], '7');
        EXPECT_EQ(str5[6], '\0');

        String str6 = {str4, 4};
        EXPECT_EQ(str6[0], '2');
        EXPECT_EQ(str6[1], '3');
        EXPECT_EQ(str6[3], '7');
        EXPECT_EQ(str6[4], '\0');
    }

    static void equalityOperators() noexcept {
        IT("should compare dose two strings have equal value");
        String str = {"some text", 9};
        EXPECT_EQ(str, str);
        EXPECT_EQ((String{"1234.56789", 10}), (String{"1234.56789", 10}));
        EXPECT_EQ((String{nullptr, 0}), (String{nullptr, 0}));
        EXPECT_EQ((String{"", 0}), (String{"", 0}));
        EXPECT_EQ((String{"text", 4}), (String{"text", 4}));
        EXPECT_EQ((String{"Verry verry long text :)", 25}), (String{"Verry verry long text :)", 25}));
        EXPECT_EQ((String{"", 0}), (String{nullptr, 0}));
        EXPECT_FALSE((String{"text", 4}) == (String{"txt", 3}));
        EXPECT_FALSE((String{"", 0}) == (String{"0", 1}));
        EXPECT_FALSE((String{nullptr, 0}) == (String{"0", 1}));
        EXPECT_FALSE((String{"12345", 5}) == (String{"123.45", 6}));
        EXPECT_FALSE((String{"txt", 3}) == (String{"text", 4}));
        EXPECT_FALSE((String{"-235435", 7}) == (String{"+235435", 7}));
        EXPECT_TRUE((String{"text", 4}) != (String{"txt", 3}));
        EXPECT_TRUE((String{"", 0}) != (String{"0", 1}));
        EXPECT_TRUE((String{nullptr, 0}) != (String{"0", 1}));
        EXPECT_TRUE((String{"12345", 5}) != (String{"123.45", 6}));
        EXPECT_TRUE((String{"txt", 3}) != (String{"text", 4}));
        EXPECT_TRUE((String{"-235435", 7}) != (String{"+235435", 7}));
        EXPECT_FALSE(str != str);

        bool equal = String{str, 0, 5} == String{"some", 4};
        EXPECT_TRUE(equal);
        equal = String{str, 0, 4} == String{"some ", 5};
        EXPECT_TRUE(equal);
        equal = String{str, 5} == String{"text", 4};
        EXPECT_TRUE(equal);
        equal = String{str, 4} == String{" text", 5};
        EXPECT_TRUE(equal);
        equal = String{str, 0} == str;
        EXPECT_TRUE(equal);
        equal = String{str, 0, 0} == str;
        EXPECT_TRUE(equal);
    }

    static void lessThanOperator() noexcept {
        IT("should compare two strings lexicographically, checking is right bigger");
        String str = {"some text", 9};
        EXPECT_FALSE(str < str);
        EXPECT_FALSE((String{nullptr, 0}) < (String{"", 0}));
        EXPECT_FALSE((String{"", 0}) < (String{nullptr, 0}));
        EXPECT_FALSE((String{"0", 1}) < (String{"", 0}));
        EXPECT_FALSE((String{"abcdz", 5}) < (String{"abcde", 5}));
        EXPECT_FALSE((String{"12934.56", 8}) < (String{"12234.560", 8}));
        EXPECT_FALSE((String{"999512", 6}) < (String{"99921", 6}));
        EXPECT_FALSE((String{"1.23", 4}) < (String{"1.23", 4}));
        EXPECT_FALSE((String{"tyxt", 4}) < (String{"txt", 3}));
        EXPECT_TRUE((String{nullptr, 0}) < (String{"0", 1}));
        EXPECT_TRUE((String{"abcd", 4}) < (String{"abcde", 5}));
        EXPECT_TRUE((String{"12234.56", 8}) < (String{"12234.560", 9}));
        EXPECT_TRUE((String{"99912", 5}) < (String{"99921", 5}));
        EXPECT_TRUE((String{"0.23", 4}) < (String{"1.23", 4}));
        EXPECT_TRUE((String{"text", 4}) < (String{"txt", 3}));
    }

    static void greaterThanOperator() noexcept {
        IT("should compare two strings lexicographically, checking is left bigger");
        String str = {"some text", 9};
        EXPECT_FALSE(str > str);
        EXPECT_FALSE((String{nullptr, 0}) > (String{"", 0}));
        EXPECT_FALSE((String{"", 0}) > (String{nullptr, 0}));
        EXPECT_FALSE((String{nullptr, 0}) > (String{"0", 1}));
        EXPECT_FALSE((String{"abcd", 4}) > (String{"abcde", 5}));
        EXPECT_FALSE((String{"12234.56", 8}) > (String{"12234.560",9}));
        EXPECT_FALSE((String{"99912", 5}) > (String{"99921", 5}));
        EXPECT_FALSE((String{"0.23", 4}) > (String{"1.23", 4}));
        EXPECT_FALSE((String{"1.23", 4}) > (String{"1.23", 4}));
        EXPECT_FALSE((String{"text", 4}) > (String{"txt", 3}));
        EXPECT_TRUE((String{"0", 1}) > (String{"", 0}));
        EXPECT_TRUE((String{"abcdz", 5}) > (String{"abcde", 5}));
        EXPECT_TRUE((String{"12934.56", 8}) > (String{"12234.560", 9}));
        EXPECT_TRUE((String{"999512", 6}) > (String{"99921", 5}));
        EXPECT_TRUE((String{"tyxt", 4}) > (String{"txt", 3}));
    }
};