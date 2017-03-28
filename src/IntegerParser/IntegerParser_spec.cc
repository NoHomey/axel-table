#include "IntegerParser.h"
#include "gtest/gtest.h"
#include "../It/It.h"

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
    const char* noMatch[] = {token10, token11, token12, token13, token14, token15, token16, token17, token18, token19, token20};

    for(size_t i = 0; i < 10; ++i) {
        IntegerParser parser = {noMatch[i]};
        EXPECT_FALSE(parser.matchesType());
    }
}