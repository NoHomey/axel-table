#include "textUtils.h"
#include "gtest/gtest.h"
#include "../../It/It.h"

TEST(textUtils, isMinus) {
    IT("should return true if symbol is - and false if not");
    EXPECT_TRUE(utils::textUtils::isMinus('-'));
    EXPECT_FALSE(utils::textUtils::isMinus('+'));
    EXPECT_FALSE(utils::textUtils::isMinus('9'));
    EXPECT_FALSE(utils::textUtils::isMinus('7'));
    EXPECT_TRUE(utils::textUtils::isMinus('-'));
    EXPECT_FALSE(utils::textUtils::isMinus('a'));
    EXPECT_FALSE(utils::textUtils::isMinus('?'));
    EXPECT_FALSE(utils::textUtils::isMinus('@'));
    EXPECT_FALSE(utils::textUtils::isMinus('e'));
}

TEST(textUtils, isPlus) {
    IT("should return true if symbol is + and false if not");
    EXPECT_FALSE(utils::textUtils::isPlus('-'));
    EXPECT_TRUE(utils::textUtils::isPlus('+'));
    EXPECT_FALSE(utils::textUtils::isPlus('9'));
    EXPECT_FALSE(utils::textUtils::isPlus('7'));
    EXPECT_TRUE(utils::textUtils::isPlus('+'));
    EXPECT_FALSE(utils::textUtils::isPlus('a'));
    EXPECT_FALSE(utils::textUtils::isPlus('?'));
    EXPECT_FALSE(utils::textUtils::isPlus('@'));
    EXPECT_FALSE(utils::textUtils::isPlus('e'));
}

TEST(textUtils, isDigit) {
    IT("should return true if matches /[0-9]/ and false if not");
    const char digits[11] = "0123456789";
    const char* noneDigits = "afdsfjsfikdfksdjfk!?@#$)(+-=*^";
    for(int i = 0; i < 10; ++i) {
        EXPECT_TRUE(utils::textUtils::isDigit(digits[i]));
    }
    for(int i = 0; i < 27; ++i) {
        EXPECT_FALSE(utils::textUtils::isDigit(noneDigits[i]));
    }
}

TEST(textUtils, toDigit) {
    IT("should conver digit char to single digit as unsigned int");
    const char digits[11] = "0123456789";
    unsigned int expects[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    const char* noneDigits = "afdsfjsfikdfksdjfk!?@#$)(+-=*^";
    for(int i = 0; i < 10; ++i) {
        EXPECT_EQ(utils::textUtils::toDigit(digits[i]), expects[i]);
    }
    for(int i = 0; i < 27; ++i) {
        EXPECT_EQ(utils::textUtils::toDigit(noneDigits[i]), noneDigits[i]);
    }
}