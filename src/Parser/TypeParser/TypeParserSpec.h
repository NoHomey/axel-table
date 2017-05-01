#pragma once

#include "gtest/gtest.h"
#include "../../It/It.h"
#include "../TypeParser/TypeParser.h"
#include "../ValidationException/ValidationException.h"

template<typename Parser>
class TypeParserSpec {
public:
    static void parseWhenEmpty(ConstString& noThrow) noexcept {
        IT("should throw Empty if and only if string is empty");
        ConstString str = {""};
        Parser parser = {str};
        EXPECT_THROW(parser.parseType(), parse_exception::Empty);
        Parser parserNoThrow = {noThrow};
        EXPECT_NO_THROW(parserNoThrow.parseType());
    }

    static void parseWhenNull(ConstString& noThrow) noexcept {
        IT("should throw Null if and only if string is Null string");
        ConstString str = {nullptr};
        Parser parser = {str};
        EXPECT_THROW(parser.parseType(), parse_exception::Null);
        Parser parserNoThrow = {noThrow};
        EXPECT_NO_THROW(parserNoThrow.parseType());
    }
};