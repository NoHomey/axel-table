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

TEST(ParsedAsInteger, thrownWhenParsingDoubleFailedDueToSuccessfullyParsingToInteger) {
    IT("stores parsed integer value");
    parse_exception::ParsedAsInteger exception = {4};
    EXPECT_EQ(exception.getValue(), 4);

    parse_exception::ParsedAsInteger exception2 = {-9};
    EXPECT_EQ(exception2.getValue(), -9);
}