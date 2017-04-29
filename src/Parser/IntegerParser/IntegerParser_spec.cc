#include "IntegerParser.h"
#include "gtest/gtest.h"
#include "../../It/It.h"
#include "../ValidationException/ValidationException.h"

TEST(IntegerParser, validateWhenValid) {
    IT("should not throw any exception");
    const char* match[] = {
        "+9223372036854775807",
        "-9223372036854775807",
        "1234",
        "+43535",
        "-42",
        "0",
        "+0",
        "-0",
        "1394578",
        "+01234",
        "-001234",
        "0000001",
        "-0000017",
        "+000000234343",
        "+099"
    };
    
    for(size_t i = 0; i < 14; ++i) {
        ConstString str = {match[i]};
        IntegerParser parser = {str};
        EXPECT_NO_THROW(parser.validate());
    }
}

TEST(IntegerParser, validateWhenInputIsOutOfRange) {
    IT("should throw Limit when input is not in the range[-2^63 + 1, 2^63 - 1]");
    const char* match[] = {
        "9223372036854775808",
        "+9223372036854775808",
        "-9223372036854775808",
        "9223372036854775808",
        "+9233372036854775808",
        "-9243372036854775808",
        "9330000000000000000",
        "+9330000000000000000",
        "-9330000000000000000",
        "+00009223372036854775808",
        "-000009223372036854775808"
    };
    for(size_t i = 0; i < 11; ++i) {
        ConstString str = {match[i]};
        IntegerParser parser = {str};
        EXPECT_THROW(parser.validate(), parse_exception::Limit);
    }
}

TEST(IntegerParser, validateWhenThereIsInvalidSymbol) {
    IT("should throw InvalidSymbol if input is invalid");
    const char* match[] = {
        "+-4353",
        "+1234.",
        "-123.4",
        "1234.0",
        "+43535a",
        "-4^2",
        "@0",
        "+)0",
        "-0(",
        "9223372036854775808#",
        "++43535"
    };

    for(size_t i = 0; i < 11; ++i) {
        ConstString str = {match[i]};
        IntegerParser parser = {str};
        EXPECT_THROW(parser.validate(), parse_exception::InvalidSymbol);
    }
}

TEST(IntegerParser, validateWhenEmpty) {
    IT("should throw Empty if input is empty string");
    ConstString str = {""};
    IntegerParser parser = {str};
    EXPECT_THROW(parser.validate(), parse_exception::Empty);
}

TEST(IntegerParser, validateWhenNull) {
    IT("should throw Null if input is Null string");
    ConstString str = {nullptr};
    IntegerParser parser = {str};
    EXPECT_THROW(parser.validate(), parse_exception::Null);
}

TEST(IntegerParser, validateWhenItIsJustASignSymbol) {
    IT("should throw SingleSign if input is just a sign symbol");
    ConstString strP = {"+"};
    IntegerParser plus = {strP};
    EXPECT_THROW(plus.validate(), parse_exception::SingleSign);
    ConstString strM = {"-"};
    IntegerParser minus = {strM};
    EXPECT_THROW(minus.validate(), parse_exception::SingleSign);
}

TEST(IntegerParser, parseWhenNotValidated) {
    IT("should call validate and remeber that it was validated");
    ConstString str = {""};
    IntegerParser parser = {str};
    ConstString str2 = {nullptr};
    IntegerParser parser2 = {str2};
    EXPECT_FALSE(parser.isValidated());
    EXPECT_THROW(parser.parse(), parse_exception::Empty);
    EXPECT_TRUE(parser.isValidated());
    EXPECT_FALSE(parser2.isValidated());
    EXPECT_THROW(parser2.parse(), parse_exception::Null);
    EXPECT_TRUE(parser2.isValidated());
}

TEST(IntegerParser, parse) {
    IT("parses a valid integer string to long long");
    const char* match[] = {
        "+9223372036854775807",
        "-9223372036854775807",
        "1234",
        "+43535",
        "-42",
        "0",
        "+0",
        "-0",
        "456245",
        "-001234",
        "0000001",
        "-0000017",
        "+000000234343",
        "+099",
        "+00009223372036854775807",
        "-000009223372036854775807"
    };
    const long long expect[] = {9223372036854775807, -9223372036854775807, 1234, 43535, -42, 0, 0, 0, 456245,
        -1234, 1, -17, 234343, 99, 9223372036854775807, -9223372036854775807};
    
    for(size_t i = 0; i < 16; ++i) {
        ConstString str = {match[i]};
        IntegerParser parser = {str};
        EXPECT_EQ(parser.parse(), expect[i]);
    }
}