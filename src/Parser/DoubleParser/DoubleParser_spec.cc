#include "DoubleParser.h"
#include "../IntegerParser/IntegerParserSpec.h"
#include "../TypeParser/TypeParserSpec.h"
#include "DoubleParserSpec.h"

template class TypeParserSpec<DoubleParser>;

template class IntegerParserSpec<DoubleParser>;

template class DoubleParserSpec<DoubleParser>;

static void validDoubleExpecter(DoubleParser& parser, const double expect) noexcept {
    EXPECT_NO_THROW(parser.validateType());
    EXPECT_DOUBLE_EQ(parser.parseType(), expect);
}

TEST(DoubleParser, pareseTypeWhenParsingValid) {
    DoubleParserSpec<DoubleParser>::parseValid(validDoubleExpecter);
}

TEST(DoubleParser, validateTypeWhenParsingDoubleWithMoreThan15Digits) {
    DoubleParserSpec<DoubleParser>::validateLossOfPrecision();
}

TEST(DoubleParser, validateTypeWhenParsingSingleFloatingPoint) {
    DoubleParserSpec<DoubleParser>::validateSingleFloatingPoint();
}

TEST(DoubleParser, validateTypeWhenItIsParsingInteger) {
    DoubleParserSpec<DoubleParser>::parseValidInteger();
}

TEST(DoubleParser, validateTypeWhenParsingIncompleteDouble) {
    DoubleParserSpec<DoubleParser>::validateIncompleteDouble();
}

TEST(DoubleParser, validateTypeWhenParsingDoubleWhichHasNoIntegerPart) {
    DoubleParserSpec<DoubleParser>::validateWhenDoubleHasNoIntegerPart();
}

TEST(DoubleParser, validateTypeWhenParsingEmptyString) {
    TypeParserSpec<DoubleParser>::validateWhenEmpty({"123.45", 6});
}

TEST(DoubleParser, validateTypeWhenItIsJustASignSymbol) {
    IntegerParserSpec<DoubleParser>::validateSingleSign();
}

TEST(DoubleParser, validateTypeWhenParsingIntegerWhichIOutOfRange) {
    IntegerParserSpec<DoubleParser>::validateOutOfRange();
}

TEST(DoubleParser, validateTypeWhenThereIsInvalidSymbol) {
    IntegerParserSpec<DoubleParser>::validateInvalidSymbol();
    DoubleParserSpec<DoubleParser>::validateInvalidSymbol();
}
