#include "NumberParser.h"
#include "../TypeParser/TypeParserSpec.h"
#include "../../Number/NumberHelper.h"

template class TypeParserSpec<NumberParser>;

/*TEST(NumberParser, validateTypeWhenValidInteger) {
    IT("dose not throw when validating string which is valid integer");

    struct Test {
        const char* string;
        const size_t length;
    };

    Test test[] = {
        {"+922337203685477", 16},
        {"-922337203685477", 16},
        {"1234", 4},
        {"+43535", 6}, 
        {"-42", 3},
        {"0", 1},
        {"+0", 2},
        {"-0", 2},
        {"356245", 6},
        {"-001234", 7},
        {"0000001", 7},
        {"-0000017", 8},
        {"+000000234343", 13},
        {"+099", 4},
        {"+0000922337203685477", 20},
        {"-00000922337203685477", 21}
    };

    for(size_t i = 0; i < 16; ++i) {
        ConstString str = {test[i].string, test[i].length};
        NumberParser parser = {str};
        EXPECT_NO_THROW(parser.validateType());
    }
}*/

TEST(NumberParser, validateTypeWhenSingleSign) {
    IT("should throw SingleSign if input is just a sign symbol (+ or -)");
    ConstString strPlus = {"+", 1};
    NumberParser plus = {strPlus};
    EXPECT_THROW(plus.validateType(), parse_exception::SingleSign);
    ConstString strMinus = {"-", 1};
    NumberParser minus = {strMinus};
    EXPECT_THROW(minus.validateType(), parse_exception::SingleSign);
}

TEST(NumberParser, validateTypeWhenSingleFloatingPoint) {
    IT("throws SingleFloatingPoint if is is parsing just a floating pint with no digits");
    ConstString str = {".", 1};
    NumberParser parser = {str};
    EXPECT_THROW(parser.validateType(), parse_exception::SingleFloatingPoint);
    ConstString strPlus = {"+.", 2};
    NumberParser parserPlus = {strPlus};
    EXPECT_THROW(parserPlus.validateType(), parse_exception::SingleFloatingPoint);
    ConstString strMinus = {"-.", 2};
    NumberParser parserMinus = {strMinus};
    EXPECT_THROW(parserMinus.validateType(), parse_exception::SingleFloatingPoint);
}