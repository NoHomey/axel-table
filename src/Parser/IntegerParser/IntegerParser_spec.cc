#include "IntegerParser.h"

#include "IntegerParserSpec.h"

#include "../TypeParser/TypeParserSpec.h"

template class TypeParserSpec<IntegerParser>;

template class IntegerParserSpec<IntegerParser>;

/*void validIntegerExpecter(IntegerParser& parser, const long long expect) noexcept {
    EXPECT_EQ(parser.parseType(), expect);
}

TEST(IntegerParser, parseTypeWhenParsingValidInteger) {
    IntegerParserSpec<IntegerParser>::parseValid(validIntegerExpecter);
}

TEST(IntegerParser, parseTypeWhenInputIsOutOfRange) {
    IntegerParserSpec<IntegerParser>::parseOutOfRange();
}

TEST(IntegerParser, parseTypeWhenParsingEmptyString) {
    TypeParserSpec<IntegerParser>::parseWhenEmpty("12345");
}

TEST(IntegerParser, parseTypeWhenParsingNullString) {
    TypeParserSpec<IntegerParser>::parseWhenNull("12345");
}*/

TEST(IntegerParser, parseTypeWhenItIsJustASignSymbol) {
    IntegerParserSpec<IntegerParser>::parseSingleSign();
}

/*TEST(IntegerParser, parseTypeWhenThereIsInvalidSymbol) {
    IntegerParserSpec<IntegerParser>::parseWithInvalidSymbol();
    const char* match[] = {
        "+43.53",
        "+1234.2",
        "-123.4",
        "1234.0",
        "+43535.3",
        "-4.2",
        "0.23",
        "0.43",
        "-0.34",
        ".5808",
        "+435.35",
        "+000123.3535",
        "-0000.00009",
        "348.12",
        "3.144535356546"
    };

    const size_t expectPosition[] = {3, 5, 4, 4, 6, 2, 1, 1, 2, 0, 4, 7, 5, 3, 1};

    for(size_t i = 0; i < 15; ++i) {
        ConstString str = {match[i]};
        IntegerParser parser = {str};
        EXPECT_THROW(parser.parseType(), parse_exception::InvalidSymbol);
        try {
            parser.parseType();
        } catch(const parse_exception::InvalidSymbol& error) {
            EXPECT_EQ(error.getPosition(), expectPosition[i]);
            EXPECT_EQ(error.getSymbol(), '.');
        }
    }
}*/