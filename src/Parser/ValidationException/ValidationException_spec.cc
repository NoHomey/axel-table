#include "ValidationException.h"
#include "gtest/gtest.h"
#include "../../It/It.h"

TEST(InvalidSymbol, reportsInvlaidSymbolInformation) {
    IT("store invalid symbol details when validating type and it has invalid symbol");
    parse_exception::InvalidSymbol exception = {4, '#'};
    EXPECT_EQ(exception.getPosition(), 4);
    EXPECT_EQ(exception.getSymbol(), '#');

    parse_exception::InvalidSymbol exception2 = {1, '*'};
    EXPECT_EQ(exception2.getPosition(), 1);
    EXPECT_EQ(exception2.getSymbol(), '*');
}