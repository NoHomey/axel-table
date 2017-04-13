#include "numberTextUtils.h"
#include "gtest/gtest.h"
#include "../../It/It.h"

TEST(numberTextUtils, isMinus) {
    IT("should return true if symbol is - and false if not");
    EXPECT_TRUE(utils::numberTextUtils::isMinus('-'));
    EXPECT_FALSE(utils::numberTextUtils::isMinus('+'));
    EXPECT_FALSE(utils::numberTextUtils::isMinus('9'));
    EXPECT_FALSE(utils::numberTextUtils::isMinus('7'));
    EXPECT_TRUE(utils::numberTextUtils::isMinus('-'));
    EXPECT_FALSE(utils::numberTextUtils::isMinus('a'));
    EXPECT_FALSE(utils::numberTextUtils::isMinus('?'));
    EXPECT_FALSE(utils::numberTextUtils::isMinus('@'));
    EXPECT_FALSE(utils::numberTextUtils::isMinus('e'));
}

TEST(numberTextUtils, isPlus) {
    IT("should return true if symbol is + and false if not");
    EXPECT_FALSE(utils::numberTextUtils::isPlus('-'));
    EXPECT_TRUE(utils::numberTextUtils::isPlus('+'));
    EXPECT_FALSE(utils::numberTextUtils::isPlus('9'));
    EXPECT_FALSE(utils::numberTextUtils::isPlus('7'));
    EXPECT_TRUE(utils::numberTextUtils::isPlus('+'));
    EXPECT_FALSE(utils::numberTextUtils::isPlus('a'));
    EXPECT_FALSE(utils::numberTextUtils::isPlus('?'));
    EXPECT_FALSE(utils::numberTextUtils::isPlus('@'));
    EXPECT_FALSE(utils::numberTextUtils::isPlus('e'));
}

TEST(numberTextUtils, isPlusMinus) {
    IT("should return true if symbol is + or - and false if not");
    EXPECT_TRUE(utils::numberTextUtils::isPlusMinus('-'));
    EXPECT_TRUE(utils::numberTextUtils::isPlusMinus('+'));
    EXPECT_FALSE(utils::numberTextUtils::isPlusMinus('9'));
    EXPECT_FALSE(utils::numberTextUtils::isPlusMinus('7'));
    EXPECT_TRUE(utils::numberTextUtils::isPlusMinus('+'));
    EXPECT_FALSE(utils::numberTextUtils::isPlusMinus('a'));
    EXPECT_FALSE(utils::numberTextUtils::isPlusMinus('?'));
    EXPECT_FALSE(utils::numberTextUtils::isPlusMinus('@'));
    EXPECT_FALSE(utils::numberTextUtils::isPlusMinus('e'));
    EXPECT_TRUE(utils::numberTextUtils::isPlusMinus('-'));
    EXPECT_FALSE(utils::numberTextUtils::isPlusMinus('3'));
    EXPECT_FALSE(utils::numberTextUtils::isPlusMinus('*'));
}

TEST(numberTextUtils, isDigit) {
    IT("should return true if matches /[0-9]/ and false if not");
    const char digits[11] = "0123456789";
    const char* noneDigits = "afdsfjsfikdfksdjfk!?@#$)(+-=*^";
    for(int i = 0; i < 10; ++i) {
        EXPECT_TRUE(utils::numberTextUtils::isDigit(digits[i]));
    }
    for(int i = 0; i < 27; ++i) {
        EXPECT_FALSE(utils::numberTextUtils::isDigit(noneDigits[i]));
    }
}

TEST(numberTextUtils, matchesNumberBeginning) {
    IT("should return true if matches /\\-|\\+|[0-9]/ and false if not");
    const char digits[11] = "0123456789";
    const char* noneDigits = "afdsfjsfikdfksdjfk!?@#$)(&'=*^";
    for(int i = 0; i < 10; ++i) {
        EXPECT_TRUE(utils::numberTextUtils::matchesNumberBeginning(digits[i], digits[i + 1]));
        EXPECT_TRUE(utils::numberTextUtils::matchesNumberBeginning('+', digits[i]));
        EXPECT_TRUE(utils::numberTextUtils::matchesNumberBeginning('-', digits[i]));
    }
    for(int i = 0; i < 29; ++i) {
        EXPECT_FALSE(utils::numberTextUtils::matchesNumberBeginning('+', noneDigits[i]));
        EXPECT_FALSE(utils::numberTextUtils::matchesNumberBeginning('-', noneDigits[i]));
        for(int j = 0; j < 10; ++j) {
            EXPECT_FALSE(utils::numberTextUtils::matchesNumberBeginning(noneDigits[i], digits[j]));
        }
    }
}

TEST(numberTextUtils, toDigit) {
    IT("should convert digit char to single digit as unsigned int");
    const char digits[11] = "0123456789";
    unsigned int expects[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    const char* noneDigits = "afdsfjsfikdfksdjfk!?@#$)(+-=*^";
    for(int i = 0; i < 10; ++i) {
        EXPECT_EQ(utils::numberTextUtils::toDigit(digits[i]), expects[i]);
    }
    for(int i = 0; i < 27; ++i) {
        EXPECT_EQ(utils::numberTextUtils::toDigit(noneDigits[i]), noneDigits[i]);
    }
}