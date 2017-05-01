#include "DoubleParser.h"

#include "../IntegerParser/IntegerParserSpec.h"

#include "../TypeParser/TypeParserSpec.h"

#include "DoubleParserSpec.h"

template class TypeParserSpec<DoubleParser>;

template class IntegerParserSpec<DoubleParser>;

template class DoubleParserSpec<DoubleParser>;

static void validDoubleExpecter(DoubleParser& parser, const double expect) noexcept {
    EXPECT_DOUBLE_EQ(parser.parseType(), expect);
}

TEST(DoubleParser, pareseTypeWhenParsingValid) {
    DoubleParserSpec<DoubleParser>::parseValid(validDoubleExpecter);
}

TEST(DoubleParser, parseTypeWhenParsingSingleFloatingPoint) {
    DoubleParserSpec<DoubleParser>::parseWhenSingleFloatingPoint();
}

TEST(DoubleParser, parseTypeWhenParsingDoubleWithMoreThan15Digits) {
    DoubleParserSpec<DoubleParser>::parseWhenLossOfPrecision();
}

TEST(DoubleParser, parseTypeWhenItIsParsingInteger) {
    DoubleParserSpec<DoubleParser>::parseValidInteger();
}

TEST(DoubleParser, parseTypeWhenParsingIntegerWhichIOutOfRange) {
    IntegerParserSpec<DoubleParser>::parseOutOfRange();
}

TEST(DoubleParser, parseTypeWhenParsingIncompleteDouble) {
    DoubleParserSpec<DoubleParser>::parseWhenIncompleteDouble();
}

TEST(DoubleParser, parseTypeWhenParsingDoubleWhichHasNoIntegerPart) {
    DoubleParserSpec<DoubleParser>::parseWhenDoubleHasNoIntegerPart();
}

TEST(DoubleParser, parseTypeWhenParsingEmptyString) {
    TypeParserSpec<DoubleParser>::parseWhenEmpty("123.45");
}

TEST(DoubleParser, parseTypeWhenParsingNullString) {
    TypeParserSpec<DoubleParser>::parseWhenNull("123.45");
}

TEST(DoubleParser, parseTypeWhenItIsJustASignSymbol) {
    IntegerParserSpec<DoubleParser>::parseSingleSign();
}

TEST(DoubleParser, parseTypeWhenThereIsInvalidSymbol) {
    IntegerParserSpec<DoubleParser>::parseWithInvalidSymbol();
    const char* match[] = {
        "+-43.53",
        "+1234..2",
        "-123.!4",
        "1234~.0",
        "+43535a.3",
        "-4.^2",
        "@0.23",
        "+)0.43",
        "-0,34(",
        "9477.5808#",
        "++435.35",
        "+000.&3535",
        "-0000.0000.9",
        "348.12$",
        "3.14?4535.356546"
    };

    const char* expectSymbol = "-.!~a^@),#+&.$?";

    const size_t expectPosition[] = {1, 6, 5, 4, 6, 3, 0, 1, 2, 9, 1, 5, 10, 6, 4};

    for(size_t i = 0; i < 15; ++i) {
        ConstString str = {match[i]};
        DoubleParser parser = {str};
        EXPECT_THROW(parser.parseType(), parse_exception::InvalidSymbol);
        try {
            parser.parseType();
        } catch(const parse_exception::InvalidSymbol& error) {
            EXPECT_EQ(error.getPosition(), expectPosition[i]);
            EXPECT_EQ(error.getSymbol(), expectSymbol[i]);
        }
    }
}
