#include "TableParser.h"
#include "../TableCellParser/TableCellParser.h"
#include "../StringParser/StringParser.h"

#include <iostream>

TableParser::TableParser(Reader& reader) noexcept
: reader{reader}, position{0}, row{0}, column{0}  { }

bool TableParser::isWhiteSpace(char symbol) noexcept {
    return (symbol == ' ') || (symbol == '\t');
}

bool TableParser::isCellDelimiter(char symbol) noexcept {
    return symbol == ',';
}

bool TableParser::isQuotes(char symbol) noexcept {
    return symbol == '"';
}

bool TableParser::isEndOfLine(char symbol) noexcept {
    return symbol == '\n';
}

bool TableParser::isEndOfString(char symbol) noexcept {
    return symbol == '\0';
}

const TableCell* TableParser::parseString(ConstString& token) {
    size_t index = 2;
    char symbol;
    while(true) {
        symbol = token[index - 1];
        if(isEndOfLine(symbol) || isEndOfString(symbol)) {
            position += index;
            throw StringParser::MissingQuotesInTheEnd{};
        }
        if(isQuotes(symbol)) {
            const TableCell* cell;
            try{
                cell = TableCellParser::parse({token, 0, index});
            } catch(const StringParser::MissingQuotesInTheEnd& error) {
                ++index;
                continue;
            }
            position += index;
            return cell;
        }
        ++index;
    }
}

const TableCell* TableParser::parseRest(ConstString& token) {
    size_t index = 0;
    char symbol;
    bool isCellDelimiterSymbol;
    while(true) {
        symbol = token[index];
        isCellDelimiterSymbol = isCellDelimiter(symbol);
        if(isCellDelimiterSymbol || isWhiteSpace(symbol) || isEndOfLine(symbol) || isEndOfString(symbol)) {
            position += index;
            return index > 0 ? TableCellParser::parse({token, 0, index}) : TableCellParser::parse({nullptr, 0});
        }
        ++index;
    }
}

void TableParser::skipWhiteSpaces(ConstString& token) noexcept {
    char symbol = token[position];
    while(isWhiteSpace(symbol)) {
        ++position;
        symbol = token[position];
    }
}

Table TableParser::parse() {
    Table table;
    char symbol;
    const TableCell* cell;
    while(true) {
        position = 0;
        Reader::NewlineBlock block = reader.readNewlineBlock();
        if(block.size() == 0) {
            return table;
        }
        ConstString text = {block.data(), block.size()};
        while(true) {
            skipWhiteSpaces(text);
            ConstString token = {text, position};
            symbol = text[position];
            cell = isQuotes(symbol) ? parseString(token) : parseRest(token);
            table.edit({row, column}, cell);
            skipWhiteSpaces(text);
            symbol = text[position];
            ++position;
            if(isCellDelimiter(symbol)) {
                ++column;
                continue;
            }
            if(isEndOfLine(symbol)) {
                ++row;
                column = 0;
                continue;
            }
            if(isEndOfString(symbol)) {
                break;
            }
            std::cout << "ERROR at row: " << row << ", column: " << column
                << " position: " << position << " symbol: " << symbol << std::endl;
            throw "errror";
        }
    }
}