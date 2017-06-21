#pragma once

#include "../../TableCell/TableCell.h"
#include "../../String/ConstString/ConstString.h"

class TableCellParser {
public:
    static const TableCell* parseStrict(ConstString& token);

    static const TableCell* parse(ConstString& token);

private:
    static const TableCell* parseString(ConstString& token);
};