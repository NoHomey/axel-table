#include "TableCellParser.h"
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

#define CHECK_FOR_ERROR_CELL(cellType)                  \
if(token == cellType::obtainRef().getCellValue()) {     \
    return cellType::obtainPtr();                       \
}

const TableCell* TableCellParser::parseString(ConstString& token) {
    StringParser stringParser{token};
    try {
        stringParser.validateType();
    } catch(const StringParser::EmptyString& error) {
        return new StringCell{std::move(FixedSizeString{0})};
    }
    NumberParser stringNumberParser{ConstString{token, 1, token.length() - 2}};
    try {
        stringNumberParser.validateType();
    } catch(const Exception& error) {
        return new StringCell{std::move(stringParser.parseType())};
    }
    return new StringNumberCell{stringNumberParser.parseType()};
}

const TableCell* TableCellParser::parseStrict(ConstString& token) {
    NumberParser numberParser{token};
    try {
        numberParser.validateType();
    } catch(const Empty& error) {
        return EmptyCell::obtainPtr();
    } catch(const InvalidSymbol& error) {
        if((error.getSymbol() == '"') && (error.getPosition() == 0)) {
            return parseString(token);
        }
        throw error;
    }
    return new NumberCell{numberParser.parseType()};
}

const TableCell* TableCellParser::parse(ConstString& token) {
    try {
        return parseStrict(token);
    } catch(const InvalidSymbol& error) {
        if((error.getSymbol() == '#') && (error.getPosition() == 0)) {
            CHECK_FOR_ERROR_CELL(ErrorCell)
            CHECK_FOR_ERROR_CELL(CircRefCell)
            CHECK_FOR_ERROR_CELL(DivByZeroCell)
            CHECK_FOR_ERROR_CELL(RootOfNegNumCell)
            CHECK_FOR_ERROR_CELL(ZeroRaisedOnZeroCell)
        }
        throw error;
    }
}

#undef CHECK_FOR_ERROR_CELL