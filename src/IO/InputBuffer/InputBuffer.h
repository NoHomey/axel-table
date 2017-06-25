#pragma once

#include "../../Container/DynamicArray/DynamicArray.htd"

class InputBuffer: public DynamicArray<char> {
private:
    using Base = DynamicArray<char>;

public:
    InputBuffer(size_t bufferSize);

    char* obtainBufferForInput() noexcept;

    void syncSize(size_t size) noexcept;

    size_t getIndexOfLastNewline() const noexcept;
};