#include "IntegerParser.h"
#include "gtest/gtest.h"
#include "../../It/It.h"
#include "../ValidationException/ValidationException.h"

TEST(IntegerParser, parseType) {
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
        EXPECT_EQ(parser.parseType(), expect[i]);
    }
}

TEST(IntegerParser, parseTypeWhenInputIsOutOfRange) {
    IT("should throw Limit when input is not in the range[-2^63 + 1, 2^63 - 1]");
    const char* match[] = {
        "9223372036854775808",
        "+9223372036854775808",
        "9223372036854775808",
        "+9233372036854775808",
        "9330000000000000000",
        "+9330000000000000000",
        "+00009223372036854775808",
        "-9330000000000000000",
        "-9223372036854775808",
        "-9243372036854775808",
        "-000009223372036854775808"
    };
    for(size_t i = 0; i < 11; ++i) {
        ConstString str = {match[i]};
        IntegerParser parser = {str};
        EXPECT_THROW(parser.parseType(), parse_exception::Limit);
    }

    for(size_t i = 0; i < 7; ++i) {
        ConstString str = {match[i]};
        IntegerParser parser = {str};
        EXPECT_THROW(parser.parseType(), parse_exception::MaximumLimit);
    }

    for(size_t i = 7; i < 11; ++i) {
        ConstString str = {match[i]};
        IntegerParser parser = {str};
        EXPECT_THROW(parser.parseType(), parse_exception::MinimumLimit);
    }
}

TEST(IntegerParser, parseTypeWhenEmpty) {
    IT("should throw Empty if input is empty string");
    ConstString str = {""};
    IntegerParser parser = {str};
    EXPECT_THROW(parser.parseType(), parse_exception::Empty);
}

TEST(IntegerParser, parseTypeWhenNull) {
    IT("should throw Null if input is Null string");
    ConstString str = {nullptr};
    IntegerParser parser = {str};
    EXPECT_THROW(parser.parseType(), parse_exception::Null);
}

TEST(IntegerParser, parseTypeWhenItIsJustASignSymbol) {
    IT("should throw SingleSign if input is just a sign symbol");
    ConstString strP = {"+"};
    IntegerParser plus = {strP};
    EXPECT_THROW(plus.parseType(), parse_exception::SingleSign);
    ConstString strM = {"-"};
    IntegerParser minus = {strM};
    EXPECT_THROW(minus.parseType(), parse_exception::SingleSign);
}

TEST(IntegerParser, parseTypeWhenThereIsInvalidSymbol) {
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
        "94775808#",
        "++43535",
        "+000&3535",
        "-00000000!^$9"
    };

    const char* expectSymbol = "-...a^@)(#+&!";

    const size_t expectPosition[] = {1, 5, 4, 4, 6, 2, 0, 1, 2, 8, 1, 4, 9};

    for(size_t i = 0; i < 13; ++i) {
        ConstString str = {match[i]};
        IntegerParser parser = {str};
        EXPECT_THROW(parser.parseType(), parse_exception::InvalidSymbol);

        try {
            parser.parseType();
        } catch(const parse_exception::InvalidSymbol& error) {
            EXPECT_EQ(error.getPosition(), expectPosition[i]);
            EXPECT_EQ(error.getSymbol(), expectSymbol[i]);
        }
    }
}