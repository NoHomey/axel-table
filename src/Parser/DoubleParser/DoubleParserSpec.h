#pragma once

#include "gtest/gtest.h"
#include "../../It/It.h"
#include "../TypeParser/TypeParser.h"
#include "../IntegerParser/IntegerParserSpec.h"
#include "../ValidationException/ValidationException.h"

template<typename Parser>
class DoubleParserSpec {
public:
    static void parseValid(void (*expecter)(Parser&, const double)) noexcept {
        IT("parses a valid floating point number string to double");
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
            Parser parser = {str};
            expecter(parser, expect[i]);
        }
    }

    static void parseWhenSingleFloatingPoint() noexcept {
        IT("throws SingleFloatingPoint if is is parsing just a floating pint with no digits");
        ConstString str = {"."};
        Parser parser = {str};
        EXPECT_THROW(parser.parseType(), parse_exception::SingleFloatingPoint);
        ConstString strPlus = {"+."};
        Parser parserPlus = {strPlus};
        EXPECT_THROW(parserPlus.parseType(), parse_exception::SingleFloatingPoint);
        ConstString strMinus = {"-."};
        Parser parserMinus = {strMinus};
        EXPECT_THROW(parserMinus.parseType(), parse_exception::SingleFloatingPoint);
    }

    static void parseWhenLossOfPrecision() noexcept {
        IT("should throw LossOfPrecision when the parsed double contains more than 15 digits");
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
            Parser parser = {str};
            EXPECT_THROW(parser.parseType(), parse_exception::LossOfPrecision);
        }
    }

    static void DoubleValidIntegerExpecter(Parser& parser, const long long expect) noexcept {
        EXPECT_THROW(parser.parseType(), parse_exception::ParsedAsInteger);
        try {
            parser.parseType();
        } catch(const parse_exception::ParsedAsInteger& error) {
            EXPECT_EQ(error.getValue(), expect);
        }
    }

    static void parseValidInteger() noexcept {
        IntegerParserSpec<Parser>::parseValid(DoubleValidIntegerExpecter);
    }

    static void parseWhenIncompleteDouble() noexcept {
        IT("should throw IncompleteDouble when there is floating point but no digit proceed it");
        const char* match[] = {
            "922337203687.",
            "+9223372.",
            "92233720365.",
            "+922337203.",
            "92233727.",
            "+9.",
            "93300000.",
            "+9000.",
            "+0000922337.",
            "-000000000.",
            "-922337.",
            "-000001.",
            "22.",
            "-3."
        };
        for(size_t i = 0; i < 14; ++i) {
            ConstString str = {match[i]};
            Parser parser = {str};
            EXPECT_THROW(parser.parseType(), parse_exception::IncompleteDouble);
        }
    }

    static void parseWhenDoubleHasNoIntegerPart() noexcept {
        IT("should throw DoubleHasNoIntegerPart when there is floating point but no digit is before it");
        const char* match[] = {
            ".922337203687",
            "+.9223372",
            ".92233720365",
            "+.922337203",
            ".92233727",
            "+.9",
            ".93300000",
            "+.9000",
            "+.0000922337",
            "-.000000000",
            "-.922337",
            "-.000001",
            ".22",
            ".3"
        };
        for(size_t i = 0; i < 14; ++i) {
            ConstString str = {match[i]};
            Parser parser = {str};
            EXPECT_THROW(parser.parseType(), parse_exception::DoubleHasNoIntegerPart);
        }
    }
};