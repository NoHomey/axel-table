#include "numberTextUtils.h"
#include "gtest/gtest.h"
#include "../../It/It.h"
#include "../ValidationException/ValidationException.h"

TEST(numberTextUtils, isMinus) {
    IT("should return true if symbol is - and false if not");
    EXPECT_TRUE(numberTextUtils::isMinus('-'));
    EXPECT_FALSE(numberTextUtils::isMinus('+'));
    EXPECT_FALSE(numberTextUtils::isMinus('9'));
    EXPECT_FALSE(numberTextUtils::isMinus('7'));
    EXPECT_TRUE(numberTextUtils::isMinus('-'));
    EXPECT_FALSE(numberTextUtils::isMinus('a'));
    EXPECT_FALSE(numberTextUtils::isMinus('?'));
    EXPECT_FALSE(numberTextUtils::isMinus('@'));
    EXPECT_FALSE(numberTextUtils::isMinus('e'));
}

TEST(numberTextUtils, isPlus) {
    IT("should return true if symbol is + and false if not");
    EXPECT_FALSE(numberTextUtils::isPlus('-'));
    EXPECT_TRUE(numberTextUtils::isPlus('+'));
    EXPECT_FALSE(numberTextUtils::isPlus('9'));
    EXPECT_FALSE(numberTextUtils::isPlus('7'));
    EXPECT_TRUE(numberTextUtils::isPlus('+'));
    EXPECT_FALSE(numberTextUtils::isPlus('a'));
    EXPECT_FALSE(numberTextUtils::isPlus('?'));
    EXPECT_FALSE(numberTextUtils::isPlus('@'));
    EXPECT_FALSE(numberTextUtils::isPlus('e'));
}

TEST(numberTextUtils, isPlusMinus) {
    IT("should return true if symbol is + or - and false if not");
    EXPECT_TRUE(numberTextUtils::isPlusMinus('-'));
    EXPECT_TRUE(numberTextUtils::isPlusMinus('+'));
    EXPECT_FALSE(numberTextUtils::isPlusMinus('9'));
    EXPECT_FALSE(numberTextUtils::isPlusMinus('7'));
    EXPECT_TRUE(numberTextUtils::isPlusMinus('+'));
    EXPECT_FALSE(numberTextUtils::isPlusMinus('a'));
    EXPECT_FALSE(numberTextUtils::isPlusMinus('?'));
    EXPECT_FALSE(numberTextUtils::isPlusMinus('@'));
    EXPECT_FALSE(numberTextUtils::isPlusMinus('e'));
    EXPECT_TRUE(numberTextUtils::isPlusMinus('-'));
    EXPECT_FALSE(numberTextUtils::isPlusMinus('3'));
    EXPECT_FALSE(numberTextUtils::isPlusMinus('*'));
}

TEST(numberTextUtils, isZero) {
    IT("should return true if symbol is 0 and false if not");
    const char* notZero = "a7d8f1s2i3d4k5d6fk!?@#$)(+-=*^9";

    for(int i = 0; i < 28; ++i) {
        EXPECT_FALSE(numberTextUtils::isZero(notZero[i]));
    }

    EXPECT_TRUE(numberTextUtils::isZero('0'));
}

TEST(numberTextUtils, isDigit) {
    IT("should return true if matches /[0-9]/ and false if not");
    const char digits[11] = "0123456789";
    const char* noneDigits = "afdsfjsfikdfksdjfk!?@#$)(+-=*^";
    for(int i = 0; i < 10; ++i) {
        EXPECT_TRUE(numberTextUtils::isDigit(digits[i]));
    }
    for(int i = 0; i < 27; ++i) {
        EXPECT_FALSE(numberTextUtils::isDigit(noneDigits[i]));
    }
}

TEST(numberTextUtils, toDigit) {
    IT("should convert digit char to single digit as unsigned int");
    const char digits[11] = "0123456789";
    unsigned int expects[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    const char* noneDigits = "afdsfjsfikdfksdjfk!?@#$)(+-=*^";
    for(int i = 0; i < 10; ++i) {
        EXPECT_EQ(numberTextUtils::toDigit(digits[i]), expects[i]);
    }
    for(int i = 0; i < 27; ++i) {
        EXPECT_EQ(numberTextUtils::toDigit(noneDigits[i]), noneDigits[i]);
    }
}

TEST(numberTextUtils, skipZeros) {
    IT("returns the first posions on which the char is not zero");
    const char* test[] = {
        "0003",
        "000042",
        "0999",
        "0010",
        "000000@",
        "@$%",
        "8878",
        "10",
        "9999999",
        "0000000000001"
    };

    size_t expect[] = {3, 4, 1, 2, 6, 0, 0, 0, 0, 12};

    for(size_t i = 0; i < 10; ++i) {
        ConstString str = {test[i]};
        EXPECT_EQ(numberTextUtils::skipZeros(str), expect[i]);
    }
}

TEST(numberTextUtils, containsOnlyDigits) {
    IT("should throw InvalidSymbol if the passed string contains none digit char");

    struct Test {
        const char* string;
        const char symbol;
        const size_t position;
    };

    Test test[] = {
        {"+-4353", '+', 0},
        {"+1234.", '+', 0},
        {"-123.4", '-', 0},
        {"1234.0", '.', 4},
        {"143535a", 'a', 6}, 
        {"14^2", '^', 2},
        {"@0",'@', 0},
        {"2)0", ')', 1},
        {"30(", '(', 2},
        {"92233725808#", '#', 11} ,
        {"++43535", '+', 0}
    };

    for(size_t i = 0; i < 11; ++i) {
        ConstString str = {test[i].string};
        EXPECT_THROW(numberTextUtils::containsOnlyDigits(str), parse_exception::InvalidSymbol);
        try {
            numberTextUtils::containsOnlyDigits(str);
        } catch(const parse_exception::InvalidSymbol& error) {
            EXPECT_EQ(error.getSymbol(), test[i].symbol);
            EXPECT_EQ(error.getPosition(), test[i].position);
        }
    }

    IT("returns string length if it contains only digits");

    const char* match[] = {
        "9223372036854775807",
        "9223372036854775807",
        "1234",
        "435359",
        "42",
        "0",
        "9",
        "5",
        "1394578",
        "01234",
        "001234",
        "0000001",
        "00000179",
        "0000002343439",
        "0999"
    };

    size_t expect[] = {19, 19, 4, 6, 2, 1, 1, 1, 7, 5, 6, 7, 8, 13, 4};

    for(size_t i = 0; i < 14; ++i) {
        ConstString str = {match[i]};
        EXPECT_EQ(numberTextUtils::containsOnlyDigits(str), expect[i]);
    }
}

TEST(numberTextUtils, throwLimitException) {
    EXPECT_THROW(numberTextUtils::throwLimitException('-'), parse_exception::MinimumLimit);
    EXPECT_THROW(numberTextUtils::throwLimitException('+'), parse_exception::MaximumLimit);
    EXPECT_THROW(numberTextUtils::throwLimitException('0'), parse_exception::MaximumLimit);
    EXPECT_THROW(numberTextUtils::throwLimitException('-'), parse_exception::MinimumLimit);
}