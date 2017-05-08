#include "StringParser.h"
#include "../TypeParser/TypeParserSpec.h"

template class TypeParserSpec<StringParser>;

TEST(NotEscapedQuotes, reportsNotEscapedQuotesAtTheGivenPosition) {
    IT("store the position on which unescaped quotes symbol is found");
    EXPECT_EQ(StringParser::NotEscapedQuotes{5}.getPosition(), 5);
    EXPECT_EQ(StringParser::NotEscapedQuotes{6}.getPosition(), 6);
}

TEST(AloneBackslash, reportsAloneBackslashAtTheGivenPosition) {
    IT("store the position on which alone backslash symbol is found");
    EXPECT_EQ(StringParser::AloneBackslash{3}.getPosition(), 3);
    EXPECT_EQ(StringParser::AloneBackslash{7}.getPosition(), 7);
}

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

TEST(StringParser, validateTypeWhenParsingEmptyString) {
    TypeParserSpec<StringParser>::validateWhenEmpty({"\"string\"", 8});
}

TEST(StringParser, validateTypeWhenItIsEmptyString) {
    ConstString str = {"\"\"", 2};
    StringParser parser = {str};
    EXPECT_THROW(parser.validateType(), StringParser::EmptyString);
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
        EXPECT_THROW(parser.validateType(), StringParser::MissingQuotes);
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
        EXPECT_THROW(parser.validateType(), StringParser::MissingQuotesInTheBeginng);
    }

    for(size_t i = 5; i < 11; ++i) {
        ConstString str = {test[i].string, test[i].length};
        StringParser parser = {str};
        EXPECT_THROW(parser.validateType(), StringParser::MissingQuotesInTheEnd);
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
        EXPECT_THROW(parser.validateType(), StringParser::AloneBackslash);
        try {
            parser.validateType();
        } catch(const StringParser::AloneBackslash& error) {
            EXPECT_EQ(error.getPosition(), test[i].position);
        }
    }
}

TEST(StringParser, validateTypeWhenParsingStringIncludesUnEscapedQuotes) {
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
        EXPECT_THROW(parser.validateType(), StringParser::NotEscapedQuotes);
        try {
            parser.validateType();
        } catch(const StringParser::NotEscapedQuotes& error) {
            EXPECT_EQ(error.getPosition(), test[i].position);
        }
    }
}