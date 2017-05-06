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

        struct Test {
            const char* string;
            const size_t length;
            const double expect;
        };

        Test test[] = {
            {"+9223372.0367", 13, 9223372.0367}, 
            {"-0000.9223372036", 16, -0.9223372036},
            {"12.34", 5, 12.34},
            {"+43.535", 7, 43.535},
            {"-42.3", 5, -42.3},
            {"0.1", 3, 0.1},
            {"+0.2", 4, 0.2},
            {"-0.6", 4, -0.6},
            {"1394.578", 8, 1394.578},
            {"+012.34", 7, 12.34},
            {"-001.234", 8, -1.234},
            {"0000.001", 8, 0.001},
            {"-000.0017", 9, -0.0017},
            {"+0000.00234343", 14, 0.00234343},
            {"+0.99", 5, 0.99},
            {"223334.444777777", 16, 223334.444777777},
            {"4254535435.65463", 16, 4254535435.65463},
            {"+223334.444777777", 17, 223334.444777777},
            {"+4254535435.65463", 17, 4254535435.65463},
            {"-223334.444777777", 17, -223334.444777777},
            {"-4254535435.65463", 17, -4254535435.65463},
            {"+000223334.444777777", 20, 223334.444777777},
            {"-0004254535435.65463", 20, -4254535435.65463}
        };
        
        for(size_t i = 0; i < 23; ++i) {
            ConstString str = {test[i].string, test[i].length};
            Parser parser = {str};
            expecter(parser, test[i].expect);
        }
    }

    static void parseWhenLossOfPrecision() noexcept {
        IT("should throw LossOfPrecision when the parsed double contains more than 15 digits");

        struct Test {
            const char* string;
            const size_t length;
        };

        Test test[] = {
            {"92233720368547.75808", 21},
            {"+9223372.036854775808", 22},
            {"92233720368.14778", 17},
            {"+92720310.68545808", 18},
            {"0.92233720368547808", 20},
            {"+9.233372054775808", 19},
            {"93300000.000233434", 19},
            {"+93300000.00000003", 19},
            {"+0000922337.20368547344", 24},
            {"-9330000.000000000", 19},
            {"-922337.0203685773", 19},
            {"-9243372036.8547723", 20},
            {"-00000.92233720368508123", 25},
            {"-9223372036.547726", 18}
        };

        for(size_t i = 0; i < 14; ++i) {
            ConstString str = {test[i].string, test[i].length};
            Parser parser = {str};
            EXPECT_THROW(parser.parseType(), parse_exception::LossOfPrecision);
        }

        ConstString str = {"9223372036.4778", 16};
        Parser parser = {str};
        EXPECT_NO_THROW(parser.parseType());
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

    static void parseWhenSingleFloatingPoint() noexcept {
        IT("throws SingleFloatingPoint if is is parsing just a floating pint with no digits");
        ConstString str = {".", 1};
        Parser parser = {str};
        EXPECT_THROW(parser.parseType(), parse_exception::SingleFloatingPoint);
        ConstString strPlus = {"+.", 2};
        Parser parserPlus = {strPlus};
        EXPECT_THROW(parserPlus.parseType(), parse_exception::SingleFloatingPoint);
        ConstString strMinus = {"-.", 2};
        Parser parserMinus = {strMinus};
        EXPECT_THROW(parserMinus.parseType(), parse_exception::SingleFloatingPoint);
    }

    static void parseWhenIncompleteDouble() noexcept {
        IT("should throw IncompleteDouble when there is floating point but no digit proceed it");

        struct Test {
            const char* string;
            const size_t length;
        };

        Test test[] = {
            {"922337203687.", 13},
            {"+9223372.", 9},
            {"92233720365.", 12},
            {"+922337203.", 11},
            {"9223372.", 8},
            {"+9.", 3},
            {"93300000.", 9},
            {"+9000.", 6},
            {"+0000922337.", 12},
            {"-00000000.", 10},
            {"-922337.", 8},
            {"-000001.", 8},
            {"22.", 3},
            {"-3.", 3}
        };
        for(size_t i = 0; i < 14; ++i) {
            ConstString str = {test[i].string, test[i].length};
            Parser parser = {str};
            EXPECT_THROW(parser.parseType(), parse_exception::IncompleteDouble);
        }
    }

    static void parseWhenDoubleHasNoIntegerPart() noexcept {
        IT("should throw DoubleHasNoIntegerPart when there is floating point but no digit is before it");

        struct Test {
            const char* string;
            const size_t length;
        };

        Test test[] = {
            {".922337203687", 13},
            {"+.9223372", 9},
            {".92233720365", 12},
            {"+.922337203", 11},
            {".92233727", 9},
            {"+.9", 3},
            {".93300000", 9},
            {"+.9000", 6},
            {"+.0000922337", 12},
            {"-.000000000", 11},
            {"-.922337", 8},
            {"-.000001", 8},
            {".22", 3},
            {".3", 2}
        };
        for(size_t i = 0; i < 14; ++i) {
            ConstString str = {test[i].string, test[i].length};
            Parser parser = {str};
            EXPECT_THROW(parser.parseType(), parse_exception::DoubleHasNoIntegerPart);
        }
    }

    static void parseWithInvalidSymbol() noexcept {
        struct Test {
            const char* string;
            const size_t length;
            const char expectSymbol;
            const size_t expectPosition;
        };

        Test test[] = {
            {"+-43.53", 7, '-', 1},
            {"+1234..2", 8, '.', 6},
            {"-123.!4", 7, '!', 5},
            {"1234~.0", 7, '~', 4},
            {"+43535a.3", 10, 'a', 6},
            {"-4.^2", 5, '^', 3},
            {"@0.23", 5, '@', 0},
            {"+)0.43", 6, ')', 1},
            {"-0,34(", 6, ',', 2},
            {"9477.5808#", 10, '#', 9},
            {"++435.35", 8, '+', 1},
            {"+000.&3535", 10, '&', 5},
            {"-0000.0000.9", 12, '.', 10},
            {"348.12$", 7, '$', 6},
            {"3.14?4535.35", 12, '?', 4}
        };

        for(size_t i = 0; i < 15; ++i) {
            ConstString str = {test[i].string, test[i].length};
            DoubleParser parser = {str};
            EXPECT_THROW(parser.parseType(), parse_exception::InvalidSymbol);
            try {
                parser.parseType();
            } catch(const parse_exception::InvalidSymbol& error) {
                EXPECT_EQ(error.getPosition(), test[i].expectPosition);
                EXPECT_EQ(error.getSymbol(), test[i].expectSymbol);
            }
        }
    }
};