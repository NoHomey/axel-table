#include "IntegerExtractor.h"
#include "gtest/gtest.h"
#include "../../It/It.h"

TEST(IntegerExtractor, IntegerExtractor) {
    IT("extracts integer from string and stores it and the position after the last extracted digit");

    struct Test {
        const char* string;
        long long integer;
        size_t extractionEnd;
    };

    Test test[] = {
        {"+12534", 12534, 6},
        {"-12543", -12543, 6},
        {"012543", 12543, 6},
        {"12543", 12543, 5},
        {"1", 1, 1},
        {"-1", -1, 2},
        {"+1", 1, 2},
        {"00001", 1, 5}, 
        {"", 0, 0},
        {"23a234", 23, 2},
        {"0&as24", 0, 1},
        {"-0asa233", 0, 2},
        {"+0f39es", 0, 2},
        {"a", 0, 0},
        {"#", 0, 0},
        {"+1253467890", 1253467890, 11},
        {"-1253467890", -1253467890, 11},
        {"0001253467890", 1253467890, 13},
        {"1253467890", 1253467890, 10},
        {nullptr, 0, 0}
    };

    for(size_t i = 0; i < 20; ++i) {
        ConstString str = {test[i].string};
        IntegerExtractor extractor = {str};
        EXPECT_EQ(extractor.getInteger(), test[i].integer);
        EXPECT_EQ(extractor.getExtractionEnd(), test[i].extractionEnd);
    }
}