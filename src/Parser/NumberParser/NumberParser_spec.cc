#include "NumberParser.h"
#include "../TypeParser/TypeParserSpec.h"

template class TypeParserSpec<NumberParser>;

TEST(NumberParser, validatingAndParsingValidInteger) {
    IT("dose not throw when validating string which is valid integer");

    struct Test {
        const char* string;
        const size_t length;
        const long long expect;
    };

    Test test[] = {
        {"+9223372036854778", 17, 9223372036854778},
        {"-9223372036854778", 17, -9223372036854778},
        {"1234", 4, 1234},
        {"+43535", 6, 43535}, 
        {"-42", 3, -42},
        {"0", 1, 0},
        {"+0", 2, 0},
        {"-0", 2, 0},
        {"356245", 6, 356245},
        {"-001234", 7, -1234},
        {"0000001", 7, 1},
        {"-0000017", 8, -17},
        {"+000000234343", 13, 234343},
        {"+099", 4, 99},
        {"+00009223372036854778", 21, 9223372036854778},
        {"-000009223372036854778", 22, -9223372036854778},
        {"+9223372036854778.0000", 22, 9223372036854778},
        {"-9223372036854778.0000000", 25, -9223372036854778},
        {"1234.00000000000000000000", 25, 1234},
        {"+43535.0", 8, 43535}, 
        {"-42.00000000000000000000000000000000000000", 42, -42},
        {"0.0000000000000000000000000000000000000000000", 45, 0},
        {"+0.0", 4, 0},
        {"-0.00", 5, 0},
        {"356245.000000", 13, 356245},
        {"-001234.00", 10, -1234},
        {"0000001.000000000000000000000000000", 35, 1},
        {"-0000017.0000", 13, -17},
        {"+000000234343.0", 15, 234343},
        {"+099.000000000", 14, 99},
        {"+00009223372036854778.0000000000000", 35, 9223372036854778},
        {"-000009223372036854778.000000000000", 35, -9223372036854778}
    };

    for(size_t i = 0; i < 32; ++i) {
        ConstString str = {test[i].string, test[i].length};
        NumberParser parser = {str};
        EXPECT_NO_THROW(parser.validateType());
        EXPECT_EQ(parser.parseType().getInteger(), test[i].expect);
    }
}
TEST(NumberParser, validatingAndParsingValidRealNumber) {
    IT("dose not throw when validating string which is valid real number");

    struct Test {
        const char* string;
        const size_t length;
        const double expect;
    };

    Test test[] = {
        {"+9223372.0367", 13, 9223372.0367}, 
        {"-0000.9223372036", 16, -0.9223372036},
        {"12.34", 5, 12.34},
        {"+43.535", 7, 43.535},
        {"-42.3", 5, -42.3},
        {"0.1", 3, 0.1},
        {"+0.2", 4, 0.2},
        {"-0.6", 4, -0.6},
        {"1394.578", 8, 1394.578},
        {"+012.34", 7, 12.34},
        {"-001.234", 8, -1.234},
        {"0000.001", 8, 0.001},
        {"-000.0017", 9, -0.0017},
        {"+0000.00234343", 14, 0.00234343},
        {"+0.99", 5, 0.99},
        {"223334.444777777", 16, 223334.444777777},
        {"4254535435.65463", 16, 4254535435.65463},
        {"+223334.444777777", 17, 223334.444777777},
        {"+4254535435.65463", 17, 4254535435.65463},
        {"-223334.444777777", 17, -223334.444777777},
        {"-4254535435.65463", 17, -4254535435.65463},
        {"+000223334.444777777", 20, 223334.444777777},
        {"-0004254535435.65463", 20, -4254535435.65463}
    };
        
    for(size_t i = 0; i < 23; ++i) {
        ConstString str = {test[i].string, test[i].length};
        NumberParser parser = {str};
        EXPECT_NO_THROW(parser.validateType());
        EXPECT_DOUBLE_EQ(parser.parseType().getReal(), test[i].expect);
    }
}

TEST(NumberParser, validateTypeWhenParsingEmptyString) {
    TypeParserSpec<NumberParser>::validateWhenEmpty({"123.45", 6});
}

TEST(NumberParser, validateTypeWhenSingleSign) {
    IT("should throw SingleSign if input is just a sign symbol (+ or -)");
    ConstString strPlus = {"+", 1};
    NumberParser plus = {strPlus};
    EXPECT_THROW(plus.validateType(), NumberParser::SingleSign);
    ConstString strMinus = {"-", 1};
    NumberParser minus = {strMinus};
    EXPECT_THROW(minus.validateType(), NumberParser::SingleSign);
}

TEST(NumberParser, validateTypeWhenSingleFloatingPoint) {
    IT("throws SingleFloatingPoint if is is parsing just a floating point with no digits");
    ConstString str = {".", 1};
    NumberParser parser = {str};
    EXPECT_THROW(parser.validateType(), NumberParser::SingleFloatingPoint);
    ConstString strPlus = {"+.", 2};
    NumberParser parserPlus = {strPlus};
    EXPECT_THROW(parserPlus.validateType(), NumberParser::SingleFloatingPoint);
    ConstString strMinus = {"-.", 2};
    NumberParser parserMinus = {strMinus};
    EXPECT_THROW(parserMinus.validateType(), NumberParser::SingleFloatingPoint);
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
        EXPECT_THROW(parser.validateType(), NumberParser::DoubleHasNoIntegerPart);
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
        EXPECT_THROW(parser.validateType(), NumberParser::IncompleteDouble);
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
        {"-92233720360000000", 18},
        {"000000000.00000000000000001", 27},
        {"19399439489374938.000000000", 27}
    };

    for(size_t i = 0; i < 16; ++i) {
        ConstString str = {test[i].string, test[i].length};
        NumberParser parser = {str};
        EXPECT_THROW(parser.validateType(), NumberParser::NumberIsTooLong);
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
        {"-9233720360000000", 17},
        {"000000000.0000000000000001", 26},
        {"1939943948937493.000000000", 26},
        {"00000000000000000000000000", 26},
        {"+0000000000000000000000", 23},
        {"00000000000.000000000000000", 27},
        {"-00000000.00000000000000", 24}
    };

    for(size_t i = 0; i < 20; ++i) {
        ConstString str = {testNoThrow[i].string, testNoThrow[i].length};
        NumberParser parser = {str};
        EXPECT_NO_THROW(parser.validateType());
    }
}

TEST(NumberParser, validateTypeWhenThereIsInvalidSymbol) {
    IT("throws InvalidSymbol - not a number building symbol");

    struct Test {
        const char* string;
        const size_t length;
        const char expectSymbol;
        const size_t expectPosition;
    };

    Test test[] = {
        {"+-43153", 7, '-', 1},
        {"+12342$", 7, '$', 6},
        {"-1239/4", 7, '/', 5},
        {"1234*10", 7, '*', 4},
        {"+43535z03", 10, 'z', 6},
        {"+-43.53", 7, '-', 1},
        {"+1234..2", 8, '.', 6},
        {"-123.!4", 7, '!', 5},
        {"1234~.0", 7, '~', 4},
        {"+43535a.3", 10, 'a', 6},
        {"-4.^2", 5, '^', 3},
        {"@0.23", 5, '@', 0},
        {"+-43.53", 7, '-', 1},
        {"+1234..2", 8, '.', 6},
        {"-123.!4", 7, '!', 5},
        {"1234~.0", 7, '~', 4},
        {"+43535a.3", 10, 'a', 6},
        {"-4.^2", 5, '^', 3},
        {"@0.23", 5, '@', 0},
        {"+)0.43", 6, ')', 1},
        {"-0,34(", 6, ',', 2},
        {"9477.5808#", 10, '#', 9},
        {"++435.35", 8, '+', 1},
        {"+000.&3535", 10, '&', 5},
        {"-0000.0000.9", 12, '.', 10},
        {"348.12$", 7, '$', 6},
        {"3.14?4535.35", 12, '?', 4}
    };

    for(size_t i = 0; i < 27; ++i) {
        ConstString str = {test[i].string, test[i].length};
        NumberParser parser = {str};
        EXPECT_THROW(parser.validateType(), InvalidSymbol);
        try {
            parser.validateType();
        } catch(const InvalidSymbol& error) {
            EXPECT_EQ(error.getPosition(), test[i].expectPosition);
            EXPECT_EQ(error.getSymbol(), test[i].expectSymbol);
        }
    }
}

TEST(NumberParser, parseNaturalNumber) {
    IT("parses a natural number with maximum of 16 digits");

    struct Test {
        const char* string;
        const size_t length;
        const size_t expect;
    };

    Test test[] = {
        {"1", 1,  1},
        {"2", 1,  2},
        {"9", 1,  9},
        {"10", 2,  10},
        {"42", 2,  42},
        {"73", 2,  73},
        {"100", 3,  100},
        {"123", 3,  123},
        {"456", 3,  456},
        {"987", 3,  987},
        {"999", 3,  999},
        {"1000", 4,  1000},
        {"1001", 4,  1001},
        {"2397", 4,  2397},
        {"12000", 5,  12000},
        {"14139", 5,  14139},
        {"93838", 5,  93838},
        {"120007", 6,  120007},
        {"141398", 6,  141398},
        {"938389", 6,  938389},
        {"1200073", 7,  1200073},
        {"1413984", 7,  1413984},
        {"9383895", 7,  9383895},
        {"51200073", 8,  51200073},
        {"61413984", 8,  61413984},
        {"79383895", 8,  79383895},
        {"351200073", 9,  351200073},
        {"261413984", 9,  261413984},
        {"179383895", 9,  179383895},
        {"3512050073", 10,  3512050073},
        {"2614143984", 10,  2614143984},
        {"1793833895", 10,  1793833895},
        {"35120500731", 11,  35120500731},
        {"261414398411", 12,  261414398411},
        {"1793833895111", 13,  1793833895111},
        {"35120500731333", 14,  35120500731333},
        {"261414398411333", 15,  261414398411333},
        {"1793833895111333", 16,  1793833895111333},
        {"231484392412333", 15,  231484392412333},
        {"1793833895811383", 16,  1793833895811383},
        {"8393493428899234", 16,  8393493428899234},
        {"9392038053420294", 16,  9392038053420294},
    };

    for(size_t i = 0; i < 42; ++i) {
        ConstString str = {test[i].string, test[i].length};
        NumberParser parser = {str};
        EXPECT_NO_THROW(parser.validateNaturalNumber());
        EXPECT_EQ(parser.parseNaturalNumber(), test[i].expect) << i;
    }
}

TEST(NumberParser, validateNaturalNumberWhenThereIsInvalidSymbol) {
    IT("throws InvalidSymbol");

    struct Test {
        const char* string;
        const size_t length;
        const char expectSymbol;
        const size_t expectPosition;
    };

    Test test[] = {
        {"+-43153", 7, '-', 1},
        {"+12342$", 7, '$', 6},
        {"11239/4", 7, '/', 5},
        {"1234*10", 7, '*', 4},
        {"+43535z03", 10, 'z', 6},
        {"+-43.53", 7, '-', 1},
        {"+1234..2", 8, '.', 5},
        {"2123.!4", 7, '.', 4},
        {"1234~.0", 7, '~', 4},
        {"+43535a.3", 10, 'a', 6},
        {"24.^2", 5, '.', 2},
        {"@0.23", 5, '@', 0},
        {"+-43.53", 7, '-', 1},
        {"+1234..2", 8, '.', 5},
        {"3123!14", 7, '!', 4},
        {"1234~.0", 7, '~', 4},
        {"+43535a.3", 10, 'a', 6},
        {"341.^2", 6, '.', 3},
        {"@0.23", 5, '@', 0},
        {"+)0.43", 6, ')', 1},
        {"90,34(", 6, ',', 2},
        {"9477.5808#", 10, '.', 4},
        {"++435.35", 8, '+', 1},
        {"+0000.&3535", 11, '.', 5},
        {"00000.0000.9", 12, '.', 5},
        {"348$12$", 7, '$', 3},
        {"3.14?4535.35", 12, '.', 1},
        {"--43.53", 7, '-', 0},
        {"-1234..2", 8, '-', 0},
        {"-3123!4", 7, '-', 0},
        {"-1234~0", 7, '-', 0},
        {"-43535a.3", 10, '-', 0},
    };

    for(size_t i = 0; i < 32; ++i) {
        ConstString str = {test[i].string, test[i].length};
        NumberParser parser = {str};
        EXPECT_THROW(parser.validateNaturalNumber(), InvalidSymbol);
        try {
            parser.validateNaturalNumber();
        } catch(const InvalidSymbol& error) {
            EXPECT_EQ(error.getPosition(), test[i].expectPosition) << i;
            EXPECT_EQ(error.getSymbol(), test[i].expectSymbol);
        }
    }
}

TEST(NumberParser, validateNaturalNumberWhenTokenIsIntegerZero) {
    IT("throws IntegerZero");

    struct Test {
        const char* string;
        const size_t length;
    };

    Test test[] = {
        {"+00000000000000", 15},
        {"+00000000000", 12},
        {"00000000000", 11},
        {"0", 1},
        {"+0000000", 8}
    };

    for(size_t i = 0; i < 5; ++i) {
        ConstString str = {test[i].string, test[i].length};
        NumberParser parser = {str};
        EXPECT_THROW(parser.validateNaturalNumber(), NumberParser::IntegerZero);
    }
}

TEST(NumberParser, validateNaturalNumberWhenTokenIsToLongNumber) {
    IT("throws NumberIsTooLong");

    struct Test {
        const char* string;
        const size_t length;
    };

    Test test[] = {
        {"12345678901234567", 17},
        {"123456789012345678", 18},
        {"1234567890123456719", 19},
        {"93939493299329994", 17},
        {"127245678901234567", 18},
        {"44994949292293949", 17},
        {"199202020494493930", 18},
        {"9383038394091022456", 19},
        {"81911101003030399392", 17},
        {"4040030283940550383", 18},
    };

    for(size_t i = 0; i < 10; ++i) {
        ConstString str = {test[i].string, test[i].length};
        NumberParser parser = {str};
        EXPECT_THROW(parser.validateNaturalNumber(), NumberParser::NumberIsTooLong) << i;
    }
}