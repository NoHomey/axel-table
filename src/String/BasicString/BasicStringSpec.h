#include "BasicString.h"
#include "gtest/gtest.h"
#include "../../It/It.h"

template<typename String>
class BasicStringSpec {
public:
    static void throwingBadStringOffset() noexcept {
        IT("should throw BadStringOffset if offset constructor is used and offset is bigger than length");
        String str;
        EXPECT_THROW((String{str, 2}), typename String::BadStringOffset);
        EXPECT_THROW((String{str, 1, true}), typename String::BadStringOffset);
        EXPECT_NO_THROW((String{str, 0}));
        EXPECT_NO_THROW((String{str, 0, true}));
        String str2 = {"some text"};
        EXPECT_THROW((String{str2, 10}), typename String::BadStringOffset);
        EXPECT_THROW((String{str2, 10, true}), typename String::BadStringOffset);
        EXPECT_NO_THROW((String{str2, 3}));
        EXPECT_NO_THROW((String{str2, 3, true}));
    }

    static void isNull() noexcept {
        IT("should return true if string internally is nullptr");
        String str;
        EXPECT_TRUE(str.isNull());
        EXPECT_TRUE(String{}.isNull());

        String str2 = {"1234.56789"};
        EXPECT_FALSE(str2.isNull());

        String str3 = {""};
        EXPECT_FALSE(str3.isNull());

        String str4 = {"This is a \"String\"!"};
        EXPECT_FALSE(str4.isNull());
    }

    static void isEmpty() noexcept {
        IT("should return true if string is a empty string");
        String str;
        EXPECT_FALSE(str.isEmpty());
        EXPECT_FALSE(String{}.isEmpty());
        EXPECT_FALSE(String{"0"}.isEmpty());

        String str2 = {"1234.56789"};
        EXPECT_FALSE(str2.isEmpty());

        String str3 = {""};
        EXPECT_TRUE(str3.isEmpty());
        EXPECT_TRUE(String{"\0"}.isEmpty());
        EXPECT_TRUE(String{"\0sfdsda"}.isEmpty());

        String str4 = {"This is a \"String\"!"};
        EXPECT_FALSE(str4.isEmpty());

        String str5 = {",", 1, true};
        EXPECT_TRUE(str5.isEmpty());

        String str6 = {str2, 10};
        EXPECT_TRUE(str6.isEmpty());

        String str7 = {"avcbc", 2, true};
        EXPECT_FALSE(str7.isEmpty());

        String str8 = {str7, 2};
        EXPECT_FALSE(str8.isEmpty());
    }

    static void hasContent() noexcept {
        IT("should return true if string is not Empty and it is not Null");
        String str;
        EXPECT_FALSE(str.hasContent());
        EXPECT_FALSE(String{}.hasContent());
        EXPECT_FALSE(String{""}.hasContent());
        EXPECT_TRUE(String{"0"}.hasContent());

        String str2 = {"1234.56789"};
        EXPECT_TRUE(str2.hasContent());

        String str3 = {""};
        EXPECT_FALSE(str3.hasContent());
        EXPECT_FALSE(String{"\0"}.hasContent());
        EXPECT_FALSE(String{"\0sfdsda"}.hasContent());

        String str4 = {"This is a \"String\"!"};
        EXPECT_TRUE(str4.hasContent());

        String str5 = {",", 1, true};
        EXPECT_FALSE(str5.hasContent());

        String str6 = {str2, 10};
        EXPECT_FALSE(str6.hasContent());

        String str7 = {"avcbc", 2, true};
        EXPECT_TRUE(str7.hasContent());

        String str8 = {str7, 2};
        EXPECT_TRUE(str8.hasContent());
    }

    static void length() noexcept {
        IT("should return the number of chars in the string");
        String str;
        EXPECT_EQ(str.length(), 0);

        String str2 = {"1234.56789"};
        EXPECT_EQ(str2.length(), 10);

        String str3 = {""};
        EXPECT_EQ(str3.length(), 0);

        String str4 = {"This is a \"String\"!"};
        EXPECT_EQ(str4.length(), 19);

        String str5 = {"549589358935"};
        EXPECT_EQ(str5.length(), 12);

        String str6 = {"123a4", 2, true};
        EXPECT_EQ(str6.length(), 3);

        String str7 = {"123.234\"  ", 3, true};
        EXPECT_EQ(str7.length(), 7);

        String str8 = {str7, 3};
        EXPECT_EQ(str8.length(), 4);

        String str9 = {str6, 1};
        EXPECT_EQ(str9.length(), 2);

        String str10 = {str5, 0};
        EXPECT_EQ(str10.length(), 12);

        String str11 = {str5, 0, true};
        EXPECT_EQ(str11.length(), 12);
    }

    static void cString() noexcept {
        IT("should return a non-modifiable standard C character array version of the string");
        String str;
        EXPECT_EQ(str.cString(), nullptr);
        const char* data = "some text";
        String str2 = {data};
        const char* cString = str2.cString();
        for(size_t i = 0; i < 9; ++i) {
            EXPECT_EQ(cString[i], data[i]);
        }
    }

    static void indexOperator() noexcept {
        IT("should return char at the given position or \\0 if index is out of range");
        String str;
        EXPECT_TRUE(str.isNull());
        EXPECT_EQ(str[0], '\0');
        EXPECT_EQ(str[9], '\0');

        const char* data = "1234.56789";
        String str2 = {data};
        for(size_t i = 0; data[i] != '\0'; ++i) {
            EXPECT_EQ(str2[i], data[i]);
        }
        EXPECT_EQ(str2[10], '\0');
        EXPECT_EQ(str2[100], '\0');

        String str3 = {"123.234\"  ", 3, true};
        EXPECT_EQ(str3[3], '.');
        EXPECT_EQ(str3[6], '4');
        EXPECT_EQ(str3[7], '\0');
        String str4 = {"123.2347,    ", 5, true};
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
        String str = {"some text"};
        EXPECT_EQ(str, str);
        EXPECT_EQ(String{"1234.56789"}, String{"1234.56789"});
        EXPECT_EQ(String{}, String{});
        EXPECT_EQ(String{""}, String{""});
        EXPECT_EQ(String{"text"}, String{"text"});
        EXPECT_EQ(String{"Verry verry long text :)"}, String{"Verry verry long text :)"});
        EXPECT_EQ(String{""}, String{});
        EXPECT_NE(String{"text"}, String{"txt"});
        EXPECT_NE(String{""}, String{"0"});
        EXPECT_NE(String{}, String{"0"});
        EXPECT_NE(String{"12345"}, String{"123.45"});
        EXPECT_NE(String{"txt"}, String{"text"});
        EXPECT_NE(String{"-235435"}, String{"+235435"});
        EXPECT_FALSE(str != str);

        bool equal = String{str, 5, true} == String{"some"};
        EXPECT_TRUE(equal);
        equal = String{str, 4, true} == String{"some "};
        EXPECT_TRUE(equal);
        equal = String{str, 5} == String{"text"};
        EXPECT_TRUE(equal);
        equal = String{str, 4} == String{" text"};
        EXPECT_TRUE(equal);
        equal = String{str, 0} == str;
        EXPECT_TRUE(equal);
        equal = String{str, 0, true} == str;
        EXPECT_TRUE(equal);
    }

    static void lessThanOperator() noexcept {
        IT("should compare two strings lexicographically, checking is right bigger");
        String str = {"some text"};
        EXPECT_FALSE(str < str);
        EXPECT_FALSE(String{} < String{""});
        EXPECT_FALSE(String{""} < String{});
        EXPECT_FALSE(String{"0"} < String{""});
        EXPECT_FALSE(String{"abcdz"} < String{"abcde"});
        EXPECT_FALSE(String{"12934.56"} < String{"12234.560"});
        EXPECT_FALSE(String{"999512"} < String{"99921"});
        EXPECT_FALSE(String{"1.23"} < String{"1.23"});
        EXPECT_FALSE(String{"tyxt"} < String{"txt"});
        EXPECT_TRUE(String{} < String{"0"});
        EXPECT_TRUE(String{"abcd"} < String{"abcde"});
        EXPECT_TRUE(String{"12234.56"} < String{"12234.560"});
        EXPECT_TRUE(String{"99912"} < String{"99921"});
        EXPECT_TRUE(String{"0.23"} < String{"1.23"});
        EXPECT_TRUE(String{"text"} < String{"txt"});
    }

    static void greaterThanOperator() noexcept {
        IT("should compare two strings lexicographically, checking is left bigger");
        String str = {"some text"};
        EXPECT_FALSE(str > str);
        EXPECT_FALSE(String{} > String{""});
        EXPECT_FALSE(String{""} > String{});
        EXPECT_FALSE(String{} > String{"0"});
        EXPECT_FALSE(String{"abcd"} > String{"abcde"});
        EXPECT_FALSE(String{"12234.56"} > String{"12234.560"});
        EXPECT_FALSE(String{"99912"} > String{"99921"});
        EXPECT_FALSE(String{"0.23"} > String{"1.23"});
        EXPECT_FALSE(String{"1.23"} > String{"1.23"});
        EXPECT_FALSE(String{"text"} > String{"txt"});
        EXPECT_TRUE(String{"0"} > String{""});
        EXPECT_TRUE(String{"abcdz"} > String{"abcde"});
        EXPECT_TRUE(String{"12934.56"} > String{"12234.560"});
        EXPECT_TRUE(String{"999512"} > String{"99921"});
        EXPECT_TRUE(String{"tyxt"} > String{"txt"});
    }
};