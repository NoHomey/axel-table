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
        const char* expect;
        size_t length;
    };

    Test test[] = {
        {"\"some text\"", "some text", 9},
        {"\"@#$%\"", "@#$%", 4},
        {"\"Hello world!\"", "Hello world!", 12},
        {"\"\\\\\"", "\\", 1},
        {"\"\\\"\"", "\"", 1},
        {"\"a\\\\b\"", "a\\b", 3},
        {"\"c\\\"d\"", "c\"d", 3},
        {"\"\\\\\\\"\"", "\\\"", 2},
        {"\"\\\"\\\\\"", "\"\\", 2},
        {"\"\\\\12\\\"34\"", "\\12\"34", 6},
        {"\"|\\\\\\\"\\\"\\\"|\"", "|\\\"\"\"|", 6},
        {"\"C:\\\\temp\\\\\"", "C:\\temp\\", 8},
        {"\"\\\"quote\\\"\"", "\"quote\"", 7},
        {"\"e\\\\\\\"s\\\\c\\\"ape\\\\\\\\\\\\it!\"", "e\\\"s\\c\"ape\\\\\\it!", 16}
    };

    for(size_t i = 0; i < 14; ++i) {
        ConstString str = {test[i].valid};
        StringParser parser = {str};
        FixedSizeString result;
        EXPECT_NO_THROW(result = parser.parseType());
        EXPECT_TRUE(result == ConstString{test[i].expect});
        EXPECT_EQ(result.length(), test[i].length);
    }
}

TEST(StringParser, parseTypeWhenParsingIntegerString) {
    IT("parses a valid integer string to long long");
    const char* match[] = {
        "\"+9223372036854775807\"",
        "\"-9223372036854775807\"",
        "\"1234\"",
        "\"+43535\"",
        "\"-42\"",
        "\"0\"",
        "\"+0\"",
        "\"-0\"",
        "\"456245\"",
        "\"-001234\"",
        "\"0000001\"",
        "\"-0000017\"",
        "\"+000000234343\"",
        "\"+099\"",
        "\"+00009223372036854775807\"",
        "\"-000009223372036854775807\""
    };
    const long long expect[] = {9223372036854775807, -9223372036854775807, 1234, 43535, -42, 0, 0, 0,
        456245, -1234, 1, -17, 234343, 99, 9223372036854775807, -9223372036854775807};
    
    for(size_t i = 0; i < 16; ++i) {
        ConstString str = {match[i]};
        StringParser parser = {str};
        EXPECT_THROW(parser.parseType(), parse_exception::ParsedAsInteger);
        try {
            parser.parseType();
        } catch(const parse_exception::ParsedAsInteger& error) {
            EXPECT_EQ(error.getValue(), expect[i]);
        }
    }
}

TEST(StringParser, parseTypeWhenParsingDoubleString) {
    IT("parses a valid double string to double");
    const char* match[] = {
        "\"+9223372.0367\"",
        "\"-0000.9223372036\"",
        "\"12.34\"",
        "\"+43.535\"",
        "\"-42.3\"",
        "\"0.1\"",
        "\"+0.2\"",
        "\"-0.6\"",
        "\"1394.578\"",
        "\"+012.34\"",
        "\"-001.234\"",
        "\"0000.001\"",
        "\"-000.0017\"",
        "\"+0000.00234343\"",
        "\"+0.99\"",
        "\"223334.444777777\"",
        "\"4254535435.65463\""
    };

    double expect[] = {
        9223372.0367,
        -0.9223372036,
        12.34,
        43.535,
        -42.3,
        0.1,
        0.2,
        -0.6,
        1394.578,
        12.34,
        -1.234,
        0.001,
        -0.0017,
        0.00234343,
        0.99,
        223334.444777777,
        4254535435.65463
    };

    for(size_t i = 0; i < 17; ++i) {
        ConstString str = {match[i]};
        StringParser parser = {str};
        EXPECT_THROW(parser.parseType(), parse_exception::ParsedAsDouble);
        try {
            parser.parseType();
        } catch(const parse_exception::ParsedAsDouble& error) {
            EXPECT_EQ(error.getValue(), expect[i]);
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

TEST(StringParser, pareseTypeWhenItParsesDouble) {
    DoubleParserSpec<StringParser>::parseValid(stringValidDoubleExpecter);
}

TEST(StringParser, parseTypeWhenParsingDoubleWithMoreThan15Digits) {
    DoubleParserSpec<StringParser>::parseWhenLossOfPrecision();
}

TEST(StringParser, pareseTypeWhenParsingSingleFloatingPoint) {
    DoubleParserSpec<StringParser>::parseWhenSingleFloatingPoint();
}

TEST(StringParser, parseTypeWhenParsingDoubleWhichHasNoIntegerPart) {
    DoubleParserSpec<StringParser>::parseWhenDoubleHasNoIntegerPart();
}

TEST(StringParser, parseTypeWhenParsingInteger) {
    DoubleParserSpec<StringParser>::parseValidInteger();
}

TEST(StringParser, parseTypeWhenParsingIntegerWhichIsOutOfRange) {
    IntegerParserSpec<StringParser>::parseOutOfRange();
}

TEST(StringParser, parseTypeWhenParsingIncompleteDouble) {
    DoubleParserSpec<StringParser>::parseWhenIncompleteDouble();
}

TEST(StringParser, parseTypeWhenParsingEmptyString) {
    TypeParserSpec<StringParser>::parseWhenEmpty("\"string\"");
}

TEST(StringParser, parseTypeWhenParsingNullString) {
    TypeParserSpec<StringParser>::parseWhenNull("\"string\"");
}

TEST(StringParser, parseTypeWhenItIsJustASignSymbol) {
    IntegerParserSpec<StringParser>::parseSingleSign();
}

TEST(StringParser, parseTypeWhenParsingStringWithNoContent) {
    ConstString str = {"\"\""};
    StringParser parser = {str};
    EXPECT_THROW(parser.parseType(), parse_exception::EmptyString);
}

TEST(StringParser, parseTypeWhenParsingStringWhichIsNotAnumberAndDoseNotStartWithQuotes) {
    IT("throws MissingQuotes if the string it's not a number but it dose not have quotes");

    const char* badInput[] = {
        "dfsfkdslfsfl;ds,",
        "@993895",
        "338.$$$",
        "some text",
        "This is String"
    };

    for(size_t i = 0; i < 4; ++i) {
        ConstString str = {badInput[i]};
        StringParser parser = {str};
        EXPECT_THROW(parser.parseType(), parse_exception::MissingQuotes);
    }
}

TEST(StringParser, parseTypeWhenParsingStringWithUnbalancedQuotes) {
    IT("throws if the string dose not start and end with quotes");

    const char* badInput[] = {
        "34424sfsf\"",
        "dfjdsifsdfl\"",
        "dfkslfjsl\"",
        "kdfsllsdfkl\\\"asdad\"",
        "\"dfsdfasdfsd",
        "\"939rfkdslfw49r",
        "\"44349.324324f",
        "\"03492,54fdsf",
        "\"0\\ \\\"",
        "\"\\\\\\\"",
        "\"\\\""
    };

    for(size_t i = 0; i < 4; ++i) {
        ConstString str = {badInput[i]};
        StringParser parser = {str};
        EXPECT_THROW(parser.parseType(), parse_exception::MissingQuotesInTheBeginng);
    }

    for(size_t i = 5; i < 11; ++i) {
        ConstString str = {badInput[i]};
        StringParser parser = {str};
        EXPECT_THROW(parser.parseType(), parse_exception::MissingQuotesInTheEnd);
    }
}

TEST(StringParser, parseTypeWhenParsingStringWichHasBackslashThatDoseNotEscapingAnything) {
    IT("throws AloneBackslash if the string includes alone backslash");

    const char* badInput[] = {
        "\"\\ \"",
        "\"aa\\bb\"",
        "\"aa\\\\\\ bb\"",
        "\"aa\\\"\\bb\"",
        "\"aa\\\"\\\\bb\\\\\\ \"",
        "\"aa\\\"\\\\bb\\\\\\\" \\\" \\ \"",
    };

    size_t position[] = {1, 3, 5, 5, 11, 17};

    for(size_t i = 0; i < 6; ++i) {
        ConstString str = {badInput[i]};
        StringParser parser = {str};
        EXPECT_THROW(parser.parseType(), parse_exception::AloneBackslash);
        try {
            parser.parseType();
        } catch(const parse_exception::AloneBackslash& error) {
            EXPECT_EQ(error.getPosition(), position[i]);
        }
    }
}

TEST(StringParser, parseTypeWhenParsingStringIncludesNotEscapedQuotes) {
    IT("throws NotEscapedQuotes if the string includes not escaped quotes");

    const char* badInput[] = {
        "\"\"\\\"\"",
        "\"aa\"bb\"",
        "\"aa\\\"\"bb\"",
        "\"aa\\\"\"bb\"",
        "\"aa\\\"\\\"bb\"\\\\\"",
        "\"aa\\\"bb\\\"\\\"\\\\\"\"",
        "\"aa\\\"bb\\\"\\\"\\\"\"\\ \"",
    };

    size_t position[] = {1, 3, 5, 5, 9, 13, 13};

    for(size_t i = 0; i < 7; ++i) {
        ConstString str = {badInput[i]};
        StringParser parser = {str};
        EXPECT_THROW(parser.parseType(), parse_exception::NotEscapedQuotes);
        try {
            parser.parseType();
        } catch(const parse_exception::NotEscapedQuotes& error) {
            EXPECT_EQ(error.getPosition(), position[i]);
        }
    }
}