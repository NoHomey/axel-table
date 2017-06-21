#pragma once

#include "../TableCell.h"
#include "../../String/ConstString/ConstString.h"
#include "../SingletonCell/SingletonCellDeclaration.mcrs"

class ErrorCell: public TableCell {
SINGLETON_CELL_DECLARATION(ErrorCell);

public:
    const Number& getValueAsNumber() const noexcept final;

    size_t calculateOutputLength() const noexcept final;

    size_t calculateSerializedLength() const noexcept final;

protected:
    ErrorCell(const char* string, size_t length) noexcept;

private:
    static const char* valueString;

    static const Number errorCellNumberValue;

    ConstString value;
};