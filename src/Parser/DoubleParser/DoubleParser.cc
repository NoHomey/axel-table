#include "DoubleParser.h"

DoubleParser::DoubleParser(ConstString& string) noexcept
: TypeParser<double>{string} {}

double DoubleParser::typeParser() const {
    return 0;
}

void DoubleParser::typeValidator() const {
    
}