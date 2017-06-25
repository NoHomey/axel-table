#include "InputBuffer.h"

InputBuffer::InputBuffer(size_t bufferSize)
: Base{bufferSize} { }

char* InputBuffer::obtainBufferForInput() noexcept {
    return array;
}

void InputBuffer::syncSize(size_t size) noexcept {
    const size_t maxSize = arrayCapacity;
    arraySize = size <= maxSize ? size : maxSize;
}

size_t InputBuffer::getIndexOfLastNewline() const noexcept {
    const size_t count = size();
    size_t index = count - 1;
    while(true) {
        if(array[index] == '\n') {
            return index;
        }
        if(index == 0) {
            return count;
        }
        --index;
    }
}