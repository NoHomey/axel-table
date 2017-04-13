#include "ValidationException.h"
#include "gtest/gtest.h"
#include "../../It/It.h"

TEST(ValidationException, reportsTypeValidationException) {
    IT("store exception details when validating type and it's not valid'");
    parse_exception::ValidationException exception = {4, 'i'};
    EXPECT_EQ(exception.getPosition(), 4);
    EXPECT_EQ(exception.getSymbol(), 'i');

    parse_exception::ValidationException exception2 = {1, '*'};
    EXPECT_EQ(exception2.getPosition(), 1);
    EXPECT_EQ(exception2.getSymbol(), '*');
}