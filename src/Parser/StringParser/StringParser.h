#pragma once

#include "../TypeParser/TypeParser.h"
#include "../../String/FixedSizeString/FixedSizeString.h"

class StringParser: public TypeParser<FixedSizeString> {
public:
    StringParser(ConstString& string) noexcept;

    StringParser(const StringParser&) = delete;

    StringParser(StringParser&&) = delete;

    StringParser& operator=(const StringParser&) = delete;

    StringParser& operator=(StringParser&&) = delete;
    
protected:
    static bool isBackslash(const char symbol) noexcept;

    static bool isQuotes(const char symbol) noexcept;

    void typeValidator() const override final;

    FixedSizeString typeParser() const override final;

private:
    static bool isCountOfBackslashesOdd(const size_t from, const size_t to) noexcept;

    size_t calculateParseResultStringLength() const noexcept;

    void validateBackslashes(const size_t length) const;
    
    void validateBackslashesBefore(const size_t lastChecked) const;
};