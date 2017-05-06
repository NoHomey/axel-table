#include "StringParser.h"
#include "../IntegerParser/IntegerParserSpec.h"
#include "../TypeParser/TypeParserSpec.h"
#include "../DoubleParser/DoubleParserSpec.h"

template class TypeParserSpec<StringParser>;

template class IntegerParserSpec<StringParser>;

template class DoubleParserSpec<StringParser>;

TEST(StringParser, parseTypeWhenParsingValidString) {
    IT("parses valid string to FixedSizeString");

    struct Test {
        const char* valid;
        const size_t strLength;
        const char* expect;
        size_t length;
    };

    Test test[] = {
        {"\"some text\"", 11, "some text", 9},
        {"\"@#$%\"", 6, "@#$%", 4},
        {"\"Hello world!\"", 14, "Hello world!", 12},
        {"\"\\\\\"", 4, "\\", 1},
        {"\"\\\"\"", 4, "\"", 1},
        {"\"a\\\\b\"", 6, "a\\b", 3},
        {"\"c\\\"d\"", 6, "c\"d", 3},
        {"\"\\\\\\\"\"", 6, "\\\"", 2},
        {"\"\\\"\\\\\"", 6, "\"\\", 2},
        {"\"\\\\12\\\"34\"", 10, "\\12\"34", 6},
        {"\"|\\\\\\\"\\\"\\\"|\"", 12, "|\\\"\"\"|", 6},
        {"\"C:\\\\temp\\\\\"", 12, "C:\\temp\\", 8},
        {"\"\\\"quote\\\"\"", 11, "\"quote\"", 7},
        {"\"e\\\\\\\"s\\\\c\\\"ape\\\\\\\\\\\\it!\"", 25, "e\\\"s\\c\"ape\\\\\\it!", 16}
    };

    for(size_t i = 0; i < 14; ++i) {
        ConstString str = {test[i].valid, test[i].strLength};
        StringParser parser = {str};
        FixedSizeString result{0};
        EXPECT_NO_THROW(result = parser.parseType());
        EXPECT_TRUE(result == (ConstString{test[i].expect, test[i].length}));
    }
}

TEST(StringParser, parseTypeWhenParsingIntegerString) {
    IT("parses a valid integer string to long long");
        
    struct Test {
        const char* string;
        const size_t length;
        const long long expect;
    };

    Test test[] = {
        {"\"+9223372036854775807\"", 22, 9223372036854775807},
        {"\"-9223372036854775807\"", 22, -9223372036854775807},
        {"\"1234\"", 6, 1234},
        {"\"+43535\"", 8, 43535}, 
        {"\"-42\"", 5, -42},
        {"\"0\"", 3, 0},
        {"\"+0\"", 4, 0},
        {"\"-0\"", 4, 0},
        {"\"356245\"", 8, 356245},
        {"\"-001234\"", 9, -1234},
        {"\"0000001\"", 9, 1},
        {"\"-0000017\"", 10, -17},
        {"\"+000000234343\"", 15, 234343},
        {"\"+099\"", 6, 99},
        {"\"+00009223372036854775807\"", 26, 9223372036854775807},
        {"\"-000009223372036854775807\"", 27, -9223372036854775807}
    };
    
    for(size_t i = 0; i < 16; ++i) {
        ConstString str = {test[i].string, test[i].length};
        StringParser parser = {str};
        EXPECT_THROW(parser.parseType(), parse_exception::ParsedAsInteger);
        try {
            parser.parseType();
        } catch(const parse_exception::ParsedAsInteger& error) {
            EXPECT_EQ(error.getValue(), test[i].expect);
        }
    }
}

TEST(StringParser, parseTypeWhenParsingDoubleString) {
    IT("parses a valid double string to double");
    
    struct Test {
        const char* string;
        const size_t length;
        const double expect;
    };

    Test test[] = {
        {"\"+9223372.0367\"", 15, 9223372.0367}, 
        {"\"-0000.9223372036\"", 18, -0.9223372036},
        {"\"12.34\"", 7, 12.34},
        {"\"+43.535\"", 9, 43.535},
        {"\"-42.3\"", 7, -42.3},
        {"\"0.1\"", 5, 0.1},
        {"\"+0.2\"", 6, 0.2},
        {"\"-0.6\"", 6, -0.6},
        {"\"1394.578\"", 10, 1394.578},
        {"\"+012.34\"", 9, 12.34},
        {"\"-001.234\"", 10, -1.234},
        {"\"0000.001\"", 10, 0.001},
        {"\"-000.0017\"", 11, -0.0017},
        {"\"+0000.00234343\"", 16, 0.00234343},
        {"\"+0.99\"", 7, 0.99},
        {"\"223334.444777777\"", 18, 223334.444777777},
        {"\"4254535435.65463\"", 18, 4254535435.65463},
        {"\"+223334.444777777\"", 19, 223334.444777777},
        {"\"+4254535435.65463\"", 19, 4254535435.65463},
        {"\"-223334.444777777\"", 19, -223334.444777777},
        {"\"-4254535435.65463\"", 19, -4254535435.65463},
        {"\"+000223334.444777777\"", 22, 223334.444777777},
        {"\"-0004254535435.65463\"", 22, -4254535435.65463}
    };

    for(size_t i = 0; i < 23; ++i) {
        ConstString str = {test[i].string, test[i].length};
        StringParser parser = {str};
        EXPECT_THROW(parser.parseType(), parse_exception::ParsedAsDouble);
        try {
            parser.parseType();
        } catch(const parse_exception::ParsedAsDouble& error) {
            EXPECT_EQ(error.getValue(), test[i].expect);
        }
    }
}

static void stringValidDoubleExpecter(StringParser& parser, const double expect) noexcept {
    EXPECT_THROW(parser.parseType(), parse_exception::ParsedAsDouble);
    try {
        parser.parseType();
    } catch(const parse_exception::ParsedAsDouble& error) {
        EXPECT_DOUBLE_EQ(error.getValue(), expect);
    }
}

TEST(StringParser, validateTypeWhenItParsesDouble) {
    DoubleParserSpec<StringParser>::parseValid(stringValidDoubleExpecter);
}

TEST(StringParser, validateTypeWhenParsingDoubleWithMoreThan15Digits) {
    DoubleParserSpec<StringParser>::validateLossOfPrecision();
}

TEST(StringParser, validateTypeWhenParsingSingleFloatingPoint) {
    DoubleParserSpec<StringParser>::validateSingleFloatingPoint();
}

TEST(StringParser, validateTypeWhenParsingDoubleWhichHasNoIntegerPart) {
    DoubleParserSpec<StringParser>::validateWhenDoubleHasNoIntegerPart();
}

TEST(StringParser, validateTypeWhenParsingInteger) {
    DoubleParserSpec<StringParser>::parseValidInteger();
}

TEST(StringParser, validateTypeWhenParsingIntegerWhichIsOutOfRange) {
    IntegerParserSpec<StringParser>::validateOutOfRange();
}

TEST(StringParser, validateTypeWhenParsingIncompleteDouble) {
    DoubleParserSpec<StringParser>::validateIncompleteDouble();
}

TEST(StringParser, validateTypeWhenParsingEmptyString) {
    TypeParserSpec<StringParser>::validateWhenEmpty({"\"string\"", 8});
}

TEST(StringParser, validateTypeWhenItIsJustASignSymbol) {
    IntegerParserSpec<StringParser>::validateSingleSign();
}

TEST(StringParser, validateTypeWhenItIsEmptyString) {
    ConstString str = {"\"\"", 2};
    StringParser parser = {str};
    EXPECT_THROW(parser.validateType(), parse_exception::EmptyString);
}

TEST(StringParser, validateTypeWhenParsingStringWhichIsNotANumberAndDoseNotStartWithQuotes) {
    IT("throws MissingQuotes if the string it's not a number but it dose not have quotes");

    struct Test {
        const char* string;
        const size_t length;
    };

    Test test[] = {
        {"dfsfkdslfsfl;ds,", 16},
        {"@993895", 7},
        {"338.$$$", 7},
        {"some text", 9},
        {"This is String", 14}
    };

    for(size_t i = 0; i < 5; ++i) {
        ConstString str = {test[i].string, test[i].length};
        StringParser parser = {str};
        EXPECT_THROW(parser.validateType(), parse_exception::MissingQuotes);
    }
}

TEST(StringParser, validateTypeWhenParsingStringWithUnbalancedQuotes) {
    IT("throws if the string dose not start and end with quotes");

    struct Test {
        const char* string;
        const size_t length;
    };

    Test test[] = {
        {"34424sfsf\"", 10},
        {"dfjdsifsdfl\"", 12},
        {"dfkslfjsl\"", 10},
        {"kdfsllsdfkl\\\"asdad\"", 19},
        {"\"dfsdfasdfsd", 12},
        {"\"939rfkdslfw49r", 15},
        {"\"44349.324324f", 14},
        {"\"03492,54fdsf", 13},
        {"\"0\\ \\\"", 6},
        {"\"\\\\\\\"", 6},
        {"\"\\\"", 3}
    };

    for(size_t i = 0; i < 4; ++i) {
        ConstString str = {test[i].string, test[i].length};
        StringParser parser = {str};
        EXPECT_THROW(parser.validateType(), parse_exception::MissingQuotesInTheBeginng);
    }

    for(size_t i = 5; i < 11; ++i) {
        ConstString str = {test[i].string, test[i].length};
        StringParser parser = {str};
        EXPECT_THROW(parser.validateType(), parse_exception::MissingQuotesInTheEnd);
    }
}

TEST(StringParser, validateTypeWhenParsingStringWichHasBackslashThatDoseNotEscapingAnything) {
    IT("throws AloneBackslash if the string includes alone backslash");

    struct Test {
         const char* string;
         const size_t length;
         const size_t position;
     };

    Test test[] = {
        {"\"\\ \"", 4, 1},
        {"\"aa\\bb\"", 7, 3},
        {"\"aa\\\\\\ bb\"", 10, 5},
        {"\"aa\\\"\\bb\"", 9, 5},
        {"\"aa\\\"\\\\bb\\\\\\ \"", 14, 11},
        {"\"aa\\\"\\\\bb\\\\\\\" \\\" \\ \"", 20, 17}
    };

    for(size_t i = 0; i < 6; ++i) {
        ConstString str = {test[i].string, test[i].length};
        StringParser parser = {str};
        EXPECT_THROW(parser.validateType(), parse_exception::AloneBackslash);
        try {
            parser.validateType();
        } catch(const parse_exception::AloneBackslash& error) {
            EXPECT_EQ(error.getPosition(), test[i].position);
        }
    }
}

TEST(StringParser, validateTypeWhenParsingStringIncludesNotEscapedQuotes) {
    IT("throws NotEscapedQuotes if the string includes not escaped quotes");

     struct Test {
         const char* string;
         const size_t length;
         const size_t position;
     };

    Test test[] = {
        {"\"\"\\\"\"", 5, 1},
        {"\"aa\"bb\"", 7, 3},
        {"\"aa\\\"\"bb\"", 11, 5},
        {"\"aa\\\"\"bb\"", 11, 5},
        {"\"aa\\\"\\\"bb\"\\\\\"", 15, 9},
        {"\"aa\\\"bb\\\"\\\"\\\\\"\"", 17, 13},
        {"\"aa\\\"bb\\\"\\\"\\\"\"\"\"", 16, 13}
    };

    for(size_t i = 0; i < 7; ++i) {
        ConstString str = {test[i].string, test[i].length};
        StringParser parser = {str};
        EXPECT_THROW(parser.validateType(), parse_exception::NotEscapedQuotes);
        try {
            parser.validateType();
        } catch(const parse_exception::NotEscapedQuotes& error) {
            EXPECT_EQ(error.getPosition(), test[i].position);
        }
    }
}