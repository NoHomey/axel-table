#include "Reader.h"

Reader::NewlineBlock::NewlineBlock(const char* blockData, size_t sizeInBytes) noexcept
: block{blockData}, blockSize{sizeInBytes} { }

const char* Reader::NewlineBlock::data() const noexcept {
    return block;
}

size_t Reader::NewlineBlock::size() const noexcept {
    return blockSize;
}

MOCKABLE_CONST size_t Reader::initialSize = 512;

MOCKABLE_CONST size_t Reader::chunkSize = 256;

Reader::Reader(InputStream& iStream) noexcept
: inputStream{iStream}, inputBuffer{initialSize} { }

void Reader::restoreState() noexcept {
    const size_t size = inputBuffer.size();
    const size_t firstAfterLastNewline = inputBuffer.getIndexOfLastNewline() + 1;
    if((size > 0) && (firstAfterLastNewline < size)) {
        const size_t difference = size - firstAfterLastNewline;
        char* buffer = inputBuffer.obtainBufferForInput();
        for(size_t index = 0; index < difference; ++index) {
            buffer[index] = buffer[firstAfterLastNewline + index];
        }
        inputBuffer.syncSize(difference);
    } else {
        inputBuffer.syncSize(0);
    }  
}

Reader::NewlineBlock Reader::readNewlineBlock() {
    if(inputStream.isEndOfFileReached()) {
        return NewlineBlock{nullptr, 0};
    }
    restoreState();
    size_t readBytes;
    size_t indexOfLastNewline;
    size_t size = inputBuffer.size();
    size_t notFilledMemorySize = inputBuffer.capacity() - size;
    char* buffer = inputBuffer.obtainBufferForInput();
    while(true) {
        readBytes = inputStream.read(buffer + size, notFilledMemorySize);
        size += readBytes;
        if(inputStream.isEndOfFileReached()) {
            return NewlineBlock{buffer, size};
        }
        if(readBytes < notFilledMemorySize) {
            throw ReaderIOException{};
        }
        inputBuffer.syncSize(size);
        indexOfLastNewline = inputBuffer.getIndexOfLastNewline();
        if(indexOfLastNewline < size) {
            return NewlineBlock{buffer, indexOfLastNewline};
        }
        inputBuffer.extend(chunkSize);
        notFilledMemorySize = chunkSize;
        buffer = inputBuffer.obtainBufferForInput();
    }
}