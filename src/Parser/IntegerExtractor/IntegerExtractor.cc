#include "IntegerExtractor.h"
#include "../numberTextUtils/numberTextUtils.h"

IntegerExtractor::IntegerExtractor(ConstString& string) noexcept
: integer{0}, extractionEnd{0} {
    const bool isNegative = numberTextUtils::isMinus(string[0]);
    const size_t firstDigit = isNegative || numberTextUtils::isPlus(string[0]) ? 1 : 0;
    extractionEnd = firstDigit + numberTextUtils::skipZeros({string, firstDigit});
    char symbol = string[extractionEnd];
    while(numberTextUtils::isDigit(symbol)) {
        integer *= 10;
        integer += numberTextUtils::toDigit(symbol);
        ++extractionEnd;
        symbol = string[extractionEnd];
    }
    if(isNegative) {
        integer *= -1;
    }
}

long long IntegerExtractor::getInteger() const noexcept {
    return integer;
}

size_t IntegerExtractor::getExtractionEnd() const noexcept {
    return extractionEnd;
}