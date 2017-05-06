#pragma once

#include "gtest/gtest.h"
#include "../../It/It.h"
#include "../TypeParser/TypeParser.h"
#include "../ValidationException/ValidationException.h"

template<typename Parser>
class IntegerParserSpec {
public:
    static void parseValid(void (*expecter)(Parser&, const long long)) noexcept {
        IT("parses a valid integer string to long long");

        struct Test {
            const char* string;
            const size_t length;
            const long long expect;
        };

        Test test[] = {
            {"+9223372036854775807", 20, 9223372036854775807},
            {"-9223372036854775807", 20, -9223372036854775807},
            {"1234", 4, 1234},
            {"+43535", 6, 43535}, 
            {"-42", 3, -42},
            {"0", 1, 0},
            {"+0", 2, 0},
            {"-0", 2, 0},
            {"356245", 6, 356245},
            {"-001234", 7, -1234},
            {"0000001", 7, 1},
            {"-0000017", 8, -17},
            {"+000000234343", 13, 234343},
            {"+099", 4, 99},
            {"+00009223372036854775807", 24, 9223372036854775807},
            {"-000009223372036854775807", 25, -9223372036854775807}
        };
        
        for(size_t i = 0; i < 16; ++i) {
            ConstString str = {test[i].string, test[i].length};
            Parser parser = {str};
            expecter(parser, test[i].expect);
        }
    }

    static void parseOutOfRange() noexcept {
        IT("should throw Limit when input is not in the range[-2^63 + 1, 2^63 - 1]");

        struct Test {
            const char* string;
            const size_t length;
        };

        Test test[] = {
            {"9223372036854775808", 19},
            {"+9223372036854775808", 20},
            {"9223372036854775809", 19},
            {"+0009233372036854775809", 23},
            {"9330000000000000000", 19},
            {"+9330000000000000000", 20},
            {"+00009223372036854775808", 24},
            {"-9330000000000000000", 20},
            {"-9223372036854775808", 20},
            {"-9243372036854775808", 20},
            {"-000009223372036854775808", 25},
            {"-0092233720368547758071223", 25},
            {"-92233720368547758011", 21} 
        };
        for(size_t i = 0; i < 13; ++i) {
            ConstString str = {test[i].string, test[i].length};
            Parser parser = {str};
            EXPECT_THROW(parser.parseType(), parse_exception::Limit);
        }

        for(size_t i = 0; i < 7; ++i) {
            ConstString str = {test[i].string, test[i].length};
            Parser parser = {str};
            EXPECT_THROW(parser.parseType(), parse_exception::MaximumLimit);
        }

        for(size_t i = 7; i < 13; ++i) {
            ConstString str = {test[i].string, test[i].length};
            Parser parser = {str};
            EXPECT_THROW(parser.parseType(), parse_exception::MinimumLimit);
        }
    }

    static void parseSingleSign() noexcept {
        IT("should throw SingleSign if input is just a sign symbol (+ or -)");
        ConstString strPlus = {"+", 1};
        Parser plus = {strPlus};
        EXPECT_THROW(plus.parseType(), parse_exception::SingleSign);
        ConstString strMinus = {"-", 1};
        Parser minus = {strMinus};
        EXPECT_THROW(minus.parseType(), parse_exception::SingleSign);
    }

    static void parseWithInvalidSymbol() noexcept {
        IT("should throw InvalidSymbol if the passed string is not of the Parser Type");

        struct Test {
            const char* string;
            const size_t length;
            const char expectSymbol;
            const char expectPosition;
        };

        Test test[] = {
            {"+-4353", 6, '-', 1},
            {"+1234f", 6, 'f', 5},
            {"-123,4", 6, ',', 4},
            {"1234*0", 6, '*', 4},
            {"+43535a", 7, 'a', 6},
            {"-4^2", 4, '^', 2},
            {"@0", 2, '@', 0},
            {"+)0", 3, ')', 1},
            {"-0(", 3, '(', 2},
            {"94775808#", 9, '#', 8},
            {"++43535", 7, '+', 1},
            {"+000&3535", 9, '&', 4},
            {"-00000000!^$9", 13, '!', 9} 
        };

        for(size_t i = 0; i < 13; ++i) {
            ConstString str = {test[i].string, test[i].length};
            Parser parser = {str};
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