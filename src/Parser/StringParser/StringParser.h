#pragma once

#include "../TypeParser/TypeParser.h"

class StringParser: public TypeParser<const char*> {
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

    const char* typeParser() const override final;

private:
    static bool isCountOfBackslashesOdd(const size_t from, const size_t to) noexcept;
    
    void checkBetween(const size_t lastChecked) const;
};