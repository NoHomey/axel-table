#pragma once

#include <cstddef>

#include "../../String/ConstString/ConstString.h"

class IntegerExtractor {
public:
    IntegerExtractor(ConstString& string) noexcept;

    IntegerExtractor(const IntegerExtractor&) = delete;

    IntegerExtractor& operator=(const IntegerExtractor&) = delete;

    long long getInteger() const noexcept;

    size_t getExtractionEnd() const noexcept;

private:
    long long integer;
    
    size_t extractionEnd;
};