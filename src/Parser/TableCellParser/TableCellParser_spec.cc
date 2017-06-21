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