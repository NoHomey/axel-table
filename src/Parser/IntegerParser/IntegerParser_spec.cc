#include "IntegerParser.h"
#include "gtest/gtest.h"
#include "../../It/It.h"
#include "../ValidationException/ValidationException.h"

TEST(IntegerParser, matchesType) {
    IT("should match tokens by emulating regexp matcher /\\+?\\-?\\d+/");
    const char* token1 = "+1234";
    const char* token2 = "-1234";
    const char* token3 = "1234";
    const char* token4 = "+43535";
    const char* token5 = "-42";
    const char* token6 = "0";
    const char* token7 = "+0";
    const char* token8 = "-0";
    const char* token9 = "1394578";
    const char* match[] = {token1, token2, token3, token4, token5, token6, token6, token7, token8, token9};
    
    for(size_t i = 0; i < 9; ++i) {
        IntegerParser parser = {match[i]};
        EXPECT_TRUE(parser.matchesType());
    }

    const char* token10 = "123.1";
    const char* token11 = "++42";
    const char* token12 = "asdfsf";
    const char* token13 = "139423\n";
    const char* token14 = "\"|\"";
    const char* token15 = "123420^2";
    const char* token16 = "123.13434";
    const char* token17 = "_7%27?sad";
    const char* token18 = "";
    const char* token19 = "\n\t\\s";
    const char* token20 = "/\\+?\\-?\\d+/";
    const char* token21 = "+";
    const char* token22 = "-";
    const char* token23 = "";
    const char* noMatch[] = {token10, token11, token12, token13, token14, token15, token16,
                            token17, token18, token19, token20, token21, token22, token23};

    for(size_t i = 0; i < 14; ++i) {
        IntegerParser parser = {noMatch[i]};
        EXPECT_FALSE(parser.matchesType());
    }
}

TEST(IntegerParser, validateWhenValid) {
    IT("should not throw any exception");
    const char* token1 = "+2147483647";
    const char* token2 = "-2147483647";
    const char* token3 = "1234";
    const char* token4 = "+43535";
    const char* token5 = "-42";
    const char* token6 = "0";
    const char* token7 = "+0";
    const char* token8 = "-0";
    const char* token9 = "1394578";
    const char* match[] = {token1, token2, token3, token4, token5, token6, token6, token7, token8, token9};
    
    for(size_t i = 0; i < 9; ++i) {
        IntegerParser parser = {match[i]};
        EXPECT_NO_THROW(parser.validate());
    }
}

TEST(IntegerParser, validateWhenInputIsOutOfRange) {
    IT("should throw Limit when input is not in the range[-2^31 + 1, 2^31 - 1]");
    const char* token1 = "2147483648";
    const char* token2 = "+2147483648";
    const char* token3 = "-2147483648";
    const char* token4 = "2147483659";
    const char* token5 = "+2147483659";
    const char* token6 = "-2147483659";
    const char* token7 = "2200000000";
    const char* token8 = "+2200000000";
    const char* token9 = "-2200000000";
    const char* match[9] = {token1, token2, token3, token4, token5, token6, token7, token8, token9};
    for(size_t i = 0; i < 9; ++i) {
        IntegerParser parser = {match[i]};
        EXPECT_THROW(parser.validate(), parse_exception::Limit);
    }
}

TEST(IntegerParser, validateWhenThereIsLeadingZero) {
    IT("should throw LeadingZero when input is not zero and starts with zero");
    const char* token1 = "+01234";
    const char* token2 = "-001234";
    const char* token3 = "01234";
    const char* token4 = "0000001";
    const char* token5 = "+0000002";
    const char* token6 = "-000001";
    const char* match[] = {token1, token2, token3, token4, token5, token6};
    
    for(size_t i = 0; i < 6; ++i) {
        IntegerParser parser = {match[i]};
        EXPECT_THROW(parser.validate(), parse_exception::LeadingZero);
    }
}

TEST(IntegerParser, validateWhenThereIsInvalidSymbol) {
    IT("should throw InvalidSymbol if input is invalid");
    const char* token1 = "+1234.";
    const char* token2 = "-123.4";
    const char* token3 = "1234.0";
    const char* token4 = "+43535a";
    const char* token5 = "-4^2";
    const char* token6 = "@0";
    const char* token7 = "+)0";
    const char* token8 = "-0(";
    const char* token9 = "2147483648#";
    const char* match[] = {token1, token2, token3, token4, token5, token6, token6, token7, token8, token9};
    
    for(size_t i = 0; i < 9; ++i) {
        IntegerParser parser = {match[i]};
        EXPECT_THROW(parser.validate(), parse_exception::InvalidSymbol);
    }
}

TEST(IntegerParser, validateWhenEmpty) {
    IT("should throw Empty if input is empty string");
    IntegerParser parser = {""};
    EXPECT_THROW(parser.validate(), parse_exception::Empty);
}

TEST(IntegerParser, validateWhenNull) {
    IT("should throw Empty if input is empty string");
    IntegerParser parser = {nullptr};
    EXPECT_THROW(parser.validate(), parse_exception::Null);
}

TEST(IntegerParser, parseWhenNotValidated) {
    IT("should call validate and remeber that it was validated");
    StringObject str = {""};
    IntegerParser parser = {str};
    EXPECT_FALSE(parser.isValidated());
    EXPECT_THROW(parser.parse(), parse_exception::Empty);
    EXPECT_TRUE(parser.isValidated());
}