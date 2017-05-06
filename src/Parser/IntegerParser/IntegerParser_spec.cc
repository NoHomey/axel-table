#include "IntegerParser.h"

#include "IntegerParserSpec.h"

#include "../TypeParser/TypeParserSpec.h"

template class TypeParserSpec<IntegerParser>;

template class IntegerParserSpec<IntegerParser>;

void validIntegerExpecter(IntegerParser& parser, const long long expect) noexcept {
    EXPECT_EQ(parser.parseType(), expect);
}

TEST(IntegerParser, parseTypeWhenParsingValidInteger) {
    IntegerParserSpec<IntegerParser>::parseValid(validIntegerExpecter);
}

TEST(IntegerParser, parseTypeWhenInputIsOutOfRange) {
    IntegerParserSpec<IntegerParser>::parseOutOfRange();
}

TEST(IntegerParser, parseTypeWhenParsingEmptyString) {
    TypeParserSpec<IntegerParser>::parseWhenEmpty({"12345", 5});
}

TEST(IntegerParser, parseTypeWhenItIsJustASignSymbol) {
    IntegerParserSpec<IntegerParser>::parseSingleSign();
}

TEST(IntegerParser, parseTypeWhenThereIsInvalidSymbol) {
    IntegerParserSpec<IntegerParser>::parseWithInvalidSymbol();

    struct Test {
        const char* string;
        const size_t length;
        const size_t expect;
    };

    Test test[] = {
        {"+43.53", 6, 3},
        {"+1234.2", 7, 5},
        {"-123.4", 6, 4}, 
        {"1234.0", 6, 4},
        {"+43535.3", 8, 6},
        {"-4.2", 4, 2},
        {"0.23", 4, 1},
        {"0.43", 4, 1},
        {"-0.34", 5, 2},
        {".5808", 5, 0},
        {"+435.35", 7, 4},
        {"+000123.3535", 12, 7}, 
        {"-0000.00009", 11, 5},
        {"348.12", 7, 3},
        {"3.144535356546", 14, 1}
    };

    for(size_t i = 0; i < 15; ++i) {
        ConstString str = {test[i].string, test[i].length};
        IntegerParser parser = {str};
        EXPECT_THROW(parser.parseType(), parse_exception::InvalidSymbol);
        try {
            parser.parseType();
        } catch(const parse_exception::InvalidSymbol& error) {
            EXPECT_EQ(error.getPosition(), test[i].expect);
            EXPECT_EQ(error.getSymbol(), '.');
        }
    }
}