#pragma once

#include "../DynamicString/DynamicString.h"

class InputString: public DynamicString {
public:
    InputString(size_t bufferSize);

    char* obtainBufferForInput() noexcept;

    void syncSize(size_t size) noexcept;

    size_t getIndexOfLastNewline() const noexcept;
};