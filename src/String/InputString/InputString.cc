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

size_t InputString::getIndexOfLastNewline() const noexcept {
    const size_t size = length();
    size_t index = size;
    while(true) {
        if(string[index] == '\n') {
            return index;
        }
        if(index == 0) {
            return size;
        }
        --index;
    }
}