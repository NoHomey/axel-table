#pragma once

#include "gtest/gtest.h"
#include "../../It/It.h"
#include "../TypeParser/TypeParser.h"
#include "../ValidationException/ValidationException.h"

template<typename Parser>
class TypeParserSpec {
public:
    static void validateWhenEmpty(ConstString& noThrow) noexcept {
        IT("should throw Empty if and only if string is empty");
        ConstString str = {"", 0};
        Parser parser = {str};
        EXPECT_THROW(parser.validateType(), parse_exception::Empty);
        ConstString str2 = {nullptr, 0};
        Parser parser2 = {str2};
        EXPECT_THROW(parser2.validateType(), parse_exception::Empty);
        Parser parserNoThrow = {noThrow};
        EXPECT_NO_THROW(parserNoThrow.validateType());
    }
};