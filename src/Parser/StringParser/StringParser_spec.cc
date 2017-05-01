#include "StringParser.h"
#include "gtest/gtest.h"
#include "../../It/It.h"
#include "../ValidationException/ValidationException.h"

TEST(StringParser, parseTypeWhenParsingInteger) {
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
    const long long expect[] = {9223372036854775807, -9223372036854775807, 1234, 43535, -42, 0, 0, 0, 456245,
        -1234, 1, -17, 234343, 99, 9223372036854775807, -9223372036854775807};
    
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

TEST(StringParser, parseTypeWhenParsingDouble) {
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

TEST(StringParser, parseTypeWhenParsingStringWithUnbalancedQuotes) {
    IT("throws MissingQuotesInTheBeginng if the string dose not start and end with quotes");

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
        EXPECT_THROW(parser.parseType(), parse_exception::MissingQuotesInTheBeginng) << i;
    }

    for(size_t i = 5; i < 11; ++i) {
        ConstString str = {badInput[i]};
        StringParser parser = {str};
        EXPECT_THROW(parser.parseType(), parse_exception::MissingQuotesInTheEnd) << i;
    }
}

TEST(StringParser, parseTypeWhenParsingStringWichHasBackslashThatDoseNotEscapingAnything) {
    IT("throws AloneBackslash if the string includes alone backslash");

    const char* badInput[] = {
        "\"\\ \"",
        "\"aa\\bb\"",
        "\"aa\\\\\\bb\"",
        "\"aa\\\"\\bb\"",
        "\"aa\\\"\\\\bb\\\\\\ \"",
        "\"aa\\\"\\bb\\\\\\\" \\\" \\ \"",
    };

    for(size_t i = 0; i < 6; ++i) {
        ConstString str = {badInput[i]};
        StringParser parser = {str};
        EXPECT_THROW(parser.parseType(), parse_exception::AloneBackslash) << i;
    }
}

TEST(StringParser, parseTypeWhenParsingStringIncludesNotEscapedQuotes) {
    IT("throws NotEscapedQuotes if the string includes not escaped quotes");

    const char* badInput[] = {
        "\"\"\\\"\"",
        "\"aa\"bb\"",
        "\"aa\\\"\"bb\"",
        "\"aa\\\"\"bb\"",
        "\"aa\\\"\\\"bb\"\\\\ \"",
        "\"aa\\\"bb\\\"\\\" \\\\\"\"",
        "\"aa\\\"bb\\\"\\\" \\\" \"\\ \"",
    };

    for(size_t i = 0; i < 7; ++i) {
        ConstString str = {badInput[i]};
        StringParser parser = {str};
        EXPECT_THROW(parser.parseType(), parse_exception::NotEscapedQuotes) << i;
    }
}