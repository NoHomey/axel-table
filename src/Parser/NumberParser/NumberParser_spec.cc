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
    IT("throws SingleFloatingPoint if is is parsing just a floating point with no digits");
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

TEST(NumberParser, validateTypeWhenDoubleHasNoIntegerPart) {
    IT("should throw DoubleHasNoIntegerPart when there is floating point but no digit is before it");

    struct Test {
        const char* string;
        const size_t length;
    };

    Test test[] = {
        {".922337203687", 13},
        {"+.9223372", 9},
        {".92233720365", 12},
        {"+.922337203", 11},
        {".92233727", 9},
        {"+.9", 3},
        {".93300000", 9},
        {"+.9000", 6},
        {"+.0000922337", 12},
        {"-.000000000", 11},
        {"-.922337", 8},
        {"-.000001", 8},
        {".22", 3},
        {".3", 2}
    };

    for(size_t i = 0; i < 14; ++i) {
        ConstString str = {test[i].string, test[i].length};
        NumberParser parser = {str};
        EXPECT_THROW(parser.validateType(), parse_exception::DoubleHasNoIntegerPart);
    }
}

TEST(NumberParser, validateTypeWhenIncompleteDouble) {
    IT("should throw IncompleteDouble when there is floating point but no digit proceed it");

    struct Test {
        const char* string;
        const size_t length;
    };

    Test test[] = {
        {"922337203687.", 13},
        {"+9223372.", 9},
        {"92233720365.", 12},
        {"+922337203.", 11},
        {"9223372.", 8},
        {"+9.", 3},
        {"93300000.", 9},
        {"+9000.", 6},
        {"+0000922337.", 12},
        {"-00000000.", 10},
        {"-922337.", 8},
        {"-000001.", 8},
        {"22.", 3},
        {"-3.", 3}
    };

    for(size_t i = 0; i < 14; ++i) {
        ConstString str = {test[i].string, test[i].length};
        NumberParser parser = {str};
        EXPECT_THROW(parser.validateType(), parse_exception::IncompleteDouble);
    }
}

TEST(NumberParser, validateTypeWhenNumberIsTooLong) {
    IT("should throw NumberIsTooLong when the parsed number contains more than 16 digits");

    struct Test {
        const char* string;
        const size_t length;
    };

    Test test[] = {
        {"92233720368.758081", 18},
        {"+9223372.0000000722", 19},
        {"0.19438498949343413", 19},
        {"00000000000.19438498949343419", 29},
        {"+92720310.685458089", 19},
        {"0.92233720368547808", 19},
        {"+90.233372054775808", 19},
        {"93300000.000233434", 18},
        {"+93300000.000000032", 19},
        {"-9330000.0000000001", 19},
        {"-92233702036857732", 18},
        {"-92433720368547723", 18},
        {"-0000092233720812312345", 23},
        {"-92233720360000000", 18}
    };

    for(size_t i = 0; i < 14; ++i) {
        ConstString str = {test[i].string, test[i].length};
        NumberParser parser = {str};
        EXPECT_THROW(parser.validateType(), parse_exception::NumberIsTooLong) << i;
    }

    Test testNoThrow[] = {
        {"92233720368.75808", 17},
        {"+9223372.000000072", 18},
        {"0.194384989434341", 17},
        {"00000000000.194384989434341", 27},
        {"+92720310.68545089", 18},
        {"0.922337203685478", 17},
        {"+90.23337205477580", 18},
        {"93300000.00023434", 17},
        {"+93300000.00000002", 18},
        {"-9330000.000000001", 18},
        {"-9223370203685732", 17},
        {"-9243372038547723", 17},
        {"-000009223372082312345", 22},
        {"-9233720360000000", 17}
    };

    for(size_t i = 0; i < 14; ++i) {
        ConstString str = {testNoThrow[i].string, testNoThrow[i].length};
        NumberParser parser = {str};
        EXPECT_NO_THROW(parser.validateType()) << i;
    }
}