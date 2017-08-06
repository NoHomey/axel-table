#pragma once

#include "../../IO/Reader/Reader.h"
#include "../../Table/Table.h"
#include "../../String/ConstString/ConstString.h"

class TableParser {
public:
    TableParser(Reader& reader) noexcept;

    Table parse();

private:
    static bool isWhiteSpace(char symbol) noexcept;

    static bool isCellDelimiter(char symbol) noexcept;

    static bool isQuotes(char symbol) noexcept;

    static bool isEndOfLine(char symbol) noexcept;

    static bool isEndOfString(char symbol) noexcept;

    void skipWhiteSpaces(ConstString& token) noexcept;

    const TableCell* parseString(ConstString& token);

    const TableCell* parseRest(ConstString& token);

private:
    Reader& reader;
    size_t position;
    size_t row;
    size_t column;
};