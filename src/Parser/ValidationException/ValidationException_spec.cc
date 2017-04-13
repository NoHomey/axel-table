#include "ValidationException.h"
#include "gtest/gtest.h"
#include "../../It/It.h"

TEST(ValidationException, reportsTypeValidationException) {
    IT("store exception details when validating type and it's not valid");
    parse_exception::ValidationException exception = {4, 'i'};
    EXPECT_EQ(exception.getPosition(), 4);
    EXPECT_EQ(exception.getSymbol(), 'i');

    parse_exception::ValidationException exception2 = {1, '*'};
    EXPECT_EQ(exception2.getPosition(), 1);
    EXPECT_EQ(exception2.getSymbol(), '*');
}

TEST(Invalid, reportsTypeValidationInValidity) {
    IT("store invalid details when validating type and it's invalid");
    parse_exception::Invalid exception = {4, 'i'};
    EXPECT_EQ(exception.getPosition(), 4);
    EXPECT_EQ(exception.getSymbol(), 'i');

    parse_exception::Invalid exception2 = {1, '*'};
    EXPECT_EQ(exception2.getPosition(), 1);
    EXPECT_EQ(exception2.getSymbol(), '*');
}

TEST(Empty, reportsEmptyString) {
    IT("should reports {0, '\0'}");
    parse_exception::Empty exception;
    EXPECT_EQ(exception.getPosition(), 0);
    EXPECT_EQ(exception.getSymbol(), '\0');
}

TEST(Null, reportsNullString) {
    IT("should reports {0, '\0'}");
    parse_exception::Null exception;
    EXPECT_EQ(exception.getPosition(), 0);
    EXPECT_EQ(exception.getSymbol(), '\0');
}

TEST(SingleSign, reportsSingleSignSymbol) {
    IT("should report {1, '+'/'-'}");
    parse_exception::SingleSign plus = {'+'};
    parse_exception::SingleSign minus = {'-'};
    EXPECT_EQ(plus.getPosition(), 1);
    EXPECT_EQ(plus.getSymbol(), '+');
    EXPECT_EQ(minus.getPosition(), 1);
    EXPECT_EQ(minus.getSymbol(), '-');
}

TEST(InvalidSymbol, reportsInvlaidSymbolInformation) {
    IT("store invalid details when validating type and it has invalid symbol");
    parse_exception::InvalidSymbol exception = {4, '#'};
    EXPECT_EQ(exception.getPosition(), 4);
    EXPECT_EQ(exception.getSymbol(), '#');

    parse_exception::InvalidSymbol exception2 = {1, '*'};
    EXPECT_EQ(exception2.getPosition(), 1);
    EXPECT_EQ(exception2.getSymbol(), '*');
}

TEST(Warning, reportsTypeValidationException) {
    IT("store Warning details when validating type and Warning occurs");
    parse_exception::Warning exception = {4, 'i'};
    EXPECT_EQ(exception.getPosition(), 4);
    EXPECT_EQ(exception.getSymbol(), 'i');

    parse_exception::Warning exception2 = {1, '*'};
    EXPECT_EQ(exception2.getPosition(), 1);
    EXPECT_EQ(exception2.getSymbol(), '*');
}

TEST(Limit, reportsTypeValidationExceptionWhenLimitIsReached) {
    IT("store details when validating type and it's value is out of range");
    parse_exception::Limit exception = {10, '9'};
    EXPECT_EQ(exception.getPosition(), 10);
    EXPECT_EQ(exception.getSymbol(), '9');

    parse_exception::Limit exception2 = {2, '2'};
    EXPECT_EQ(exception2.getPosition(), 2);
    EXPECT_EQ(exception2.getSymbol(), '2');
}

TEST(LeadingZero, reportsNumberTypeValidationWhenLeadingZeroIsFound) {
    IT("store details when validating number type and it contains leading zeros");
    parse_exception::LeadingZero exception = {0};
    EXPECT_EQ(exception.getPosition(), 0);
    EXPECT_EQ(exception.getSymbol(), '0');

    parse_exception::LeadingZero exception2 = {1};
    EXPECT_EQ(exception2.getPosition(), 1);
    EXPECT_EQ(exception2.getSymbol(), '0');
}