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
    const char* tokens[] = {token1, token2, token3, token4, token5, token6, token6, token7, token8, token9};
    for(size_t i = 0; i < 9; ++i) {
        IntegerParser parser = tokens[i];
        EXPECT_TRUE(parser.matchesType());
    }
}