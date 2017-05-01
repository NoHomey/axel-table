#include "ValidationException.h"
#include "gtest/gtest.h"
#include "../../It/It.h"

TEST(InvalidSymbolAtPosition, reportsInvalidSymbolAtTheGivenPosition) {
    IT("store the position on which invalid symbol is found");
    EXPECT_EQ(parse_exception::InvalidSymbolAtPosition{4}.getPosition(), 4);
    EXPECT_EQ(parse_exception::InvalidSymbolAtPosition{9}.getPosition(), 9);
}

TEST(NotEscapedQuotes, reportsNotEscapedQuotesAtTheGivenPosition) {
    IT("store the position on which unescaped quotes symbol is found");
    EXPECT_EQ(parse_exception::NotEscapedQuotes{5}.getPosition(), 5);
    EXPECT_EQ(parse_exception::NotEscapedQuotes{6}.getPosition(), 6);
}

TEST(AloneBackslash, reportsAloneBackslashAtTheGivenPosition) {
    IT("store the position on which alone backslash symbol is found");
    EXPECT_EQ(parse_exception::AloneBackslash{3}.getPosition(), 3);
    EXPECT_EQ(parse_exception::AloneBackslash{7}.getPosition(), 7);
}

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

TEST(ParsedAsDouble, thrownWhenParsingStringFailedDueToSuccessfullyParsingToDouble) {
    IT("stores parsed double value");
    parse_exception::ParsedAsDouble exception = {0.3333};
    EXPECT_EQ(exception.getValue(), 0.3333);

    parse_exception::ParsedAsDouble exception2 = {-9.9999};
    EXPECT_EQ(exception2.getValue(), -9.9999);
}