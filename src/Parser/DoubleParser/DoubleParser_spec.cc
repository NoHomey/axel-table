#include "DoubleParser.h"
#include "gtest/gtest.h"
#include "../../It/It.h"
#include "../ValidationException/ValidationException.h"

TEST(DoubleParser, validateWhenValid) {
    IT("should not throw any exception");
    const char* match[] = {
        "+9223372.0367",
        "-0000.9223372036",
        "12.34",
        "+43.535",
        "-42.3",
        "0.1",
        "+0.2",
        "-0.6",
        "1394.578",
        "+012.34",
        "-001.234",
        "0000.001",
        "-000.0017",
        "+0000.00234343",
        "+0.99",
        "223334.444777777",
        "4254535435.65463"
    };

    double expect[] = {
        9223372.0367,
        -0.9223372036,
        12.34,
        43.535,
        -42.3,
        0.1,
        0.2,
        -0.6,
        1394.578,
        12.34,
        -1.234,
        0.001,
        -0.0017,
        0.00234343,
        0.99,
        223334.444777777,
        4254535435.65463
    };
    
    for(size_t i = 0; i < 17; ++i) {
        ConstString str = {match[i]};
        DoubleParser parser = {str};
        EXPECT_DOUBLE_EQ(parser.parseType(), expect[i]);
    }
}

TEST(DoubleParser, parseTypeWhenInputIsOutOfRange) {
    IT("should throw Limit when input is not in the range[-2^52 + 1, 2^52 - 1]");
    const char* match[] = {
        "92233720368547.75808",
        "+9223372.036854775808",
        "922337203685.4778",
        "+922337203.68545808",
        "0.92233720368547808",
        "+9.233372054775808",
        "93300000.000233434",
        "+93300000.00000003",
        "+0000922337.20368547344",
        "-9330000.000000000",
        "-922337.0203685773",
        "-9243372036.8547723",
        "-00000.92233720368508123",
        "-92233720368.54775808"
    };
    for(size_t i = 0; i < 14; ++i) {
        ConstString str = {match[i]};
        DoubleParser parser = {str};
        EXPECT_THROW(parser.parseType(), parse_exception::LossOfPrecision);
    }
}

TEST(DoubleParser, parseTypeWhenEmpty) {
    IT("should throw Empty if input is empty string");
    ConstString str = {""};
    DoubleParser parser = {str};
    EXPECT_THROW(parser.parseType(), parse_exception::Empty);
}

TEST(DoubleParser, parseTypeWhenNull) {
    IT("should throw Null if input is Null string");
    ConstString str = {nullptr};
    DoubleParser parser = {str};
    EXPECT_THROW(parser.parseType(), parse_exception::Null);
}

TEST(DoubleParser, parseTypeWhenItIsJustASignSymbol) {
    IT("should throw SingleSign if input is just a sign symbol");
    ConstString strP = {"+"};
    DoubleParser plus = {strP};
    EXPECT_THROW(plus.parseType(), parse_exception::SingleSign);
    ConstString strM = {"-"};
    DoubleParser minus = {strM};
    EXPECT_THROW(minus.parseType(), parse_exception::SingleSign);
}

TEST(DoubleParser, parseTypeWhenThereIsInvalidSymbol) {
    IT("should throw InvalidSymbol if input is invalid");
    const char* match[] = {
        "+-43.53",
        "+1234..2",
        "-123.!4",
        "1234~.0",
        "+43535a.3",
        "-4^2",
        "@0",
        "+)0",
        "-0(",
        "94775808#",
        "++43535",
        "+000&3535",
        "-00000000!^$9",
        "348.12$",
        "3.14?4535356546"
    };

    const char* expectSymbol = "-.!~a^@)(#+&!$?";

    const size_t expectPosition[] = {1, 6, 5, 4, 6, 2, 0, 1, 2, 8, 1, 4, 9, 6, 4};

    for(size_t i = 0; i < 15; ++i) {
        ConstString str = {match[i]};
        DoubleParser parser = {str};
        EXPECT_THROW(parser.parseType(), parse_exception::InvalidSymbol);
        try {
            parser.parseType();
        } catch(const parse_exception::InvalidSymbol& error) {
            EXPECT_EQ(error.getPosition(), expectPosition[i]);
            EXPECT_EQ(error.getSymbol(), expectSymbol[i]);
        }
    }
}

TEST(DoubleParser, parseTypeWhenItIsParsingInteger) {
    IT("throws ParsedAsInteger if the parsed strig is a valid Integer Type");
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
        DoubleParser parser = {str};
        EXPECT_THROW(parser.parseType(), parse_exception::ParsedAsInteger);
        try {
            parser.parseType();
        } catch(const parse_exception::ParsedAsInteger& error) {
            EXPECT_EQ(error.getValue(), expect[i]);
        }
    }
}