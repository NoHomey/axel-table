#include "ValidationException.h"
#include "gtest/gtest.h"
#include "../../It/It.h"

TEST(InvalidSymbolAtPosition, reportsInvalidSymbolAtTheGivenPosition) {
    IT("store the position on which invalid symbol is found");
    EXPECT_EQ(InvalidSymbolAtPosition{4}.getPosition(), 4);
    EXPECT_EQ(InvalidSymbolAtPosition{9}.getPosition(), 9);
}

TEST(InvalidSymbol, reportsInvlaidSymbolInformation) {
    IT("store invalid symbol details when validating type and it has invalid symbol");
    InvalidSymbol exception = {4, '#'};
    EXPECT_EQ(exception.getPosition(), 4);
    EXPECT_EQ(exception.getSymbol(), '#');

    InvalidSymbol exception2 = {1, '*'};
    EXPECT_EQ(exception2.getPosition(), 1);
    EXPECT_EQ(exception2.getSymbol(), '*');
}