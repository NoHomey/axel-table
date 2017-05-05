#include "IntegerExtractor.h"
#include "gtest/gtest.h"
#include "../../It/It.h"

TEST(IntegerExtractor, IntegerExtractor) {
    IT("extracts integer from string and stores it and the position after the last extracted digit");

    struct Test {
        const char* string;
        const size_t length;
        const long long integer;
        const size_t extractionEnd;
    };

    Test test[] = {
        {"+12534", 6, 12534, 6},
        {"-12543", 6, -12543, 6},
        {"012543", 6, 12543, 6},
        {"12543", 5, 12543, 5},
        {"1", 1, 1, 1},
        {"-1", 2, -1, 2},
        {"+1", 2, 1, 2},
        {"00001", 5, 1, 5}, 
        {"23a234", 6, 23, 2},
        {"0&as24", 6, 0, 1},
        {"-0asa233", 8, 0, 2},
        {"+0f39es", 7, 0, 2},
        {"a", 1, 0, 0},
        {"#", 1, 0, 0},
        {"+1253467890", 12, 1253467890, 11},
        {"-1253467890", 12, -1253467890, 11},
        {"0001253467890", 14, 1253467890, 13},
        {"1253467890", 10, 1253467890, 10}
    };

    for(size_t i = 0; i < 18; ++i) {
        ConstString str = {test[i].string, test[i].length};
        IntegerExtractor extractor = {str};
        EXPECT_EQ(extractor.getInteger(), test[i].integer);
        EXPECT_EQ(extractor.getExtractionEnd(), test[i].extractionEnd);
    }
}