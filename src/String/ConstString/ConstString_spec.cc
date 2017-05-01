#include "ConstString.h"

#include "../BasicString/BasicStringSpec.h"

template class BasicStringSpec<ConstString>;

TEST(ConstString, throwingBadStringOffset) {
    BasicStringSpec<ConstString>::throwingBadStringOffset();
}

TEST(ConstString, isNull) {
    BasicStringSpec<ConstString>::isNull();
}

TEST(ConstString, isEmpty) {
    BasicStringSpec<ConstString>::isEmpty();
}

TEST(ConstString, hasContent) {
    BasicStringSpec<ConstString>::hasContent();
}

TEST(ConstString, length) {
    BasicStringSpec<ConstString>::length();
}

TEST(ConstString, cString) {
    BasicStringSpec<ConstString>::cString();

    const char* data = "1234.56789";
    ConstString str2 = {data};
    EXPECT_EQ(str2.cString(), data);

    ConstString str3 = {str2, 3};
    EXPECT_EQ(str3.cString(), data + 3);

    ConstString str4 = {str2, 4};
    EXPECT_EQ(str4.cString(), data + 4);

    ConstString str5 = {str2, 1, true};
    EXPECT_EQ(str5.cString(), data);

    ConstString str6 = {str2, 0};
    EXPECT_EQ(str6.cString(), data);

    ConstString str7 = {str2, 0, true};
    EXPECT_EQ(str7.cString(), data);
}

TEST(ConstString, indexOperator) {
    BasicStringSpec<ConstString>::indexOperator();
}

TEST(ConstString, equalityOperators) {
    BasicStringSpec<ConstString>::equalityOperators();
}

TEST(ConstString, lessThanOperator) {
    BasicStringSpec<ConstString>::lessThanOperator();
}

TEST(ConstString, greaterThanOperator) {
    BasicStringSpec<ConstString>::greaterThanOperator();
}