#pragma once

#include "../TableCell.h"
#include "../../String/ConstString/ConstString.h"
#include "../SingletonCell/SingletonCellDeclaration.mcrs"
#include "../../Exception.h"

class ErrorCell: public TableCell {
SINGLETON_CELL_DECLARATION(ErrorCell);

public:
    class ErrorCellHasNoNumberValue : public Exception { };

    const Number& getValueAsNumber() const override;

    size_t calculateOutputLength() const noexcept final;

    size_t calculateSerializedLength() const noexcept final;

    bool isDeletable() const noexcept final;

    ConstString& getCellValue() const noexcept;

protected:
    ErrorCell(const char* string, size_t length) noexcept;

private:
    static const char* valueString;

    ConstString value;
};