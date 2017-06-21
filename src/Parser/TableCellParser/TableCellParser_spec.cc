#include "TableCellParser.h"
#include "gtest/gtest.h"
#include "../../It/It.h"
#include "../NumberParser/NumberParser.h"
#include "../StringParser/StringParser.h"
#include "../../TableCell/EmptyCell/EmptyCell.h"
#include "../../TableCell/NumberCell/NumberCell.h"
#include "../../TableCell/StringNumberCell/StringNumberCell.h"
#include "../../TableCell/StringCell/StringCell.h"
#include "../../TableCell/ErrorCell/ErrorCell.h"
#include "../../TableCell/CircRefCell/CircRefCell.h"
#include "../../TableCell/DivByZeroCell/DivByZeroCell.h"
#include "../../TableCell/RootOfNegNumCell/RootOfNegNumCell.h"
#include "../../TableCell/ZeroRaisedOnZeroCell/ZeroRaisedOnZeroCell.h"
#include <utility>

TEST(TableCellParser, parseErrorCell) {
    IT("returns pointer to ErrorCell if parsed string is \"#ERROR!\"");
    for(size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(TableCellParser::parse(ConstString{"#ERROR!", 7}), ErrorCell::obtainPtr());
    }
}

TEST(TableCellParser, parseCircRefCell) {
    IT("returns pointer to CircRefCell if parsed string is \"#CIRCREF!\"");
    for(size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(TableCellParser::parse(ConstString{"#CIRCREF!", 9}), CircRefCell::obtainPtr());
    }
}

TEST(TableCellParser, parseDivByZero) {
    IT("returns pointer to DivByZeroCell if parsed string is \"#DIV/0!\"");
    for(size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(TableCellParser::parse(ConstString{"#DIV/0!", 7}), DivByZeroCell::obtainPtr());
    }
}

TEST(TableCellParser, parseRootOfNegNumCell) {
    IT("returns pointer to RootOfNegNumCell if parsed string is \"#\\ROOT(-num)!\"");
    for(size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(TableCellParser::parse(ConstString{"#\\ROOT(-num)!", 13}), RootOfNegNumCell::obtainPtr());
    }
}

TEST(TableCellParser, parseZeroRaisedOnZeroCell) {
    IT("returns pointer to ZeroRaisedOnZeroCell if parsed string is \"#0^0!\"");
    for(size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(TableCellParser::parse(ConstString{"#0^0!", 5}), ZeroRaisedOnZeroCell::obtainPtr());
    }
}

TEST(TableCellParser, parseEmptyCell) {
    IT("returns pointer to EmptyCell if parsed string is empty string");
    for(size_t i = 0; i < 10; ++i) {
        EXPECT_EQ(TableCellParser::parse(ConstString{"", 0}), EmptyCell::obtainPtr());
    }
}

TEST(TableCellParser, parseEmptyString) {
    IT("returns new pointer to StringCell string with length 0 if parsed string is \"\"");
    for(size_t i = 0; i < 10; ++i) {
        const TableCell* ptr = TableCellParser::parse(ConstString{"\"\"", 2}); 
        EXPECT_EQ(ptr->getValueAsNumber().getInteger(), 0);
        EXPECT_EQ(ptr->calculateOutputLength(), 0);
        EXPECT_EQ(ptr->calculateSerializedLength(), 2);
        EXPECT_TRUE(ptr->isDeletable());
        delete ptr;
    }
}

TEST(TableCellParser, parseIntegerNumberCell) {
    IT("returns new pointer to NumberCell when the passed string is valid integer number");
    struct Test {
        const char* string;
        const size_t length;
        const size_t outputLength;
        const long long expect;
    };

    Test test[] = {
        {"+9223372036854778", 17, 16, 9223372036854778},
        {"-9223372036854778", 17, 17, -9223372036854778},
        {"1234", 4, 4, 1234},
        {"+43535", 6, 5, 43535}, 
        {"-42", 3, 3, -42},
        {"0", 1, 1, 0},
        {"+0", 2, 1, 0},
        {"-0", 2, 1, 0},
        {"356245", 6, 6, 356245},
        {"-001234", 7, 5, -1234},
        {"0000001", 7, 1, 1},
        {"-0000017", 8, 3, -17},
        {"+000000234343", 13, 6, 234343},
        {"+099", 4, 2, 99},
        {"+00009223372036854778", 21, 16, 9223372036854778},
        {"-000009223372036854778", 22, 17, -9223372036854778},
        {"+9223372036854778.0000", 22, 16, 9223372036854778},
        {"-9223372036854724.0000000", 25, 17, -9223372036854724},
        {"1234.00000000000000000000", 25, 4, 1234},
        {"+43535.0", 8, 5, 43535}, 
        {"-42.00000000000000000000000000000000000000", 42, 3, -42},
        {"0.0000000000000000000000000000000000000000000", 45, 1, 0},
        {"+0.0", 4, 1, 0},
        {"-0.00", 5, 1, 0},
        {"356245.000000", 13, 6, 356245},
        {"-001234.00", 10, 5, -1234},
        {"0000001.000000000000000000000000000", 35, 1, 1},
        {"-0000017.0000", 13, 3, -17},
        {"+000000234343.0", 15, 6, 234343},
        {"+099.000000000", 14, 2, 99},
        {"+00009223372036854778.0000000000000", 35, 16, 9223372036854778},
        {"-000009223372036854778.000000000000", 35, 17, -9223372036854778}
    };

    for(size_t i = 0; i < 32; ++i) {
        ConstString str = {test[i].string, test[i].length};
        const TableCell* ptr = TableCellParser::parse(str); 
        EXPECT_EQ(ptr->getValueAsNumber().getInteger(), test[i].expect);
        EXPECT_EQ(ptr->calculateOutputLength(), test[i].outputLength);
        EXPECT_EQ(ptr->calculateSerializedLength(), test[i].outputLength);
        EXPECT_TRUE(ptr->isDeletable());
        delete ptr;
    }
}

TEST(TableCellParser, parseIntegerStringNumberCell) {
    IT("returns new pointer to StringNumberCell when the passed string is valid integer number string");
    struct Test {
        const char* string;
        const size_t length;
        const size_t outputLength;
        const long long expect;
    };

    Test test[] = {
        {"\"+9223372036854778\"", 19, 18, 9223372036854778},
        {"\"-9223372036854778\"", 19, 19, -9223372036854778},
        {"\"1234\"", 6, 6, 1234},
        {"\"+43535\"", 8, 7, 43535}, 
        {"\"-42\"", 5, 5, -42},
        {"\"0\"", 3, 3, 0},
        {"\"+0\"", 4, 3, 0},
        {"\"-0\"", 4, 3, 0},
        {"\"356245\"", 8, 8, 356245},
        {"\"-001234\"", 9, 7, -1234},
        {"\"0000001\"", 9, 3, 1},
        {"\"-0000017\"", 10, 5, -17},
        {"\"+000000234343\"", 15, 8, 234343},
        {"\"+099\"", 6, 4, 99},
        {"\"+00009223372036854778\"", 23, 18, 9223372036854778},
        {"\"-000009223372036854778\"", 24, 19, -9223372036854778},
        {"\"+9223372036854778.0000\"", 24, 18, 9223372036854778},
        {"\"-9223372036854724.0000000\"", 27, 19, -9223372036854724},
        {"\"1234.00000000000000000000\"", 27, 6, 1234},
        {"\"+43535.0\"", 10, 7, 43535}, 
        {"\"-42.00000000000000000000000000000000000000\"", 44, 5, -42},
        {"\"0.0000000000000000000000000000000000000000000\"", 47, 3, 0},
        {"\"+0.0\"", 6, 3, 0},
        {"\"-0.00\"", 7, 3, 0},
        {"\"356245.000000\"", 15, 8, 356245},
        {"\"-001234.00\"", 12, 7, -1234},
        {"\"0000001.000000000000000000000000000\"", 37, 3, 1},
        {"\"-0000017.0000\"", 15, 5, -17},
        {"\"+000000234343.0\"", 17, 8, 234343},
        {"\"+099.000000000\"", 16, 4, 99},
        {"\"+00009223372036854778.0000000000000\"", 37, 18, 9223372036854778},
        {"\"-000009223372036854778.000000000000\"", 37, 19, -9223372036854778}
    };

    for(size_t i = 0; i < 32; ++i) {
        ConstString str = {test[i].string, test[i].length};
        const TableCell* ptr = TableCellParser::parse(str); 
        EXPECT_EQ(ptr->getValueAsNumber().getInteger(), test[i].expect);
        EXPECT_EQ(ptr->calculateOutputLength(), test[i].outputLength) ;
        EXPECT_EQ(ptr->calculateSerializedLength(), test[i].outputLength);
        EXPECT_TRUE(ptr->isDeletable());
        delete ptr;
    }
}