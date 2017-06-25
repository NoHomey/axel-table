#include "InputString.h"

InputString::InputString(size_t bufferSize)
: DynamicString{bufferSize} { }

char* InputString::obtainBufferForInput() noexcept {
    return string.array;
}

void InputString::syncSize(size_t size) noexcept {
    const size_t maxSize = string.arrayCapacity;
    string.arraySize = size > 0 ? (size < maxSize ? (size + 1) : maxSize) : size;
}