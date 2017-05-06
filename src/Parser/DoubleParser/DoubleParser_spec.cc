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

TEST(DoubleParser, parseTypeWhenParsingDoubleWithMoreThan15Digits) {
    DoubleParserSpec<DoubleParser>::parseWhenLossOfPrecision();
}

TEST(DoubleParser, parseTypeWhenParsingSingleFloatingPoint) {
    DoubleParserSpec<DoubleParser>::parseWhenSingleFloatingPoint();
}

TEST(DoubleParser, parseTypeWhenItIsParsingInteger) {
    DoubleParserSpec<DoubleParser>::parseValidInteger();
}

TEST(DoubleParser, parseTypeWhenParsingIncompleteDouble) {
    DoubleParserSpec<DoubleParser>::parseWhenIncompleteDouble();
}

TEST(DoubleParser, parseTypeWhenParsingDoubleWhichHasNoIntegerPart) {
    DoubleParserSpec<DoubleParser>::parseWhenDoubleHasNoIntegerPart();
}

TEST(DoubleParser, parseTypeWhenParsingEmptyString) {
    TypeParserSpec<DoubleParser>::parseWhenEmpty({"123.45", 6});
}

TEST(DoubleParser, parseTypeWhenItIsJustASignSymbol) {
    IntegerParserSpec<DoubleParser>::parseSingleSign();
}

TEST(DoubleParser, parseTypeWhenParsingIntegerWhichIOutOfRange) {
    IntegerParserSpec<DoubleParser>::parseOutOfRange();
}

TEST(DoubleParser, parseTypeWhenThereIsInvalidSymbol) {
    IntegerParserSpec<DoubleParser>::parseWithInvalidSymbol();
    DoubleParserSpec<DoubleParser>::parseWithInvalidSymbol();
}
