#include "Reader.h"

Reader::NewlineBlock::NewlineBlock(const char* blockData, size_t sizeInBytes) noexcept
: block{blockData}, blockSize{sizeInBytes} { }

const char* Reader::NewlineBlock::data() const noexcept {
    return block;
}

size_t Reader::NewlineBlock::size() const noexcept {
    return blockSize;
}

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
    }   
}

Reader::NewlineBlock Reader::readNewlineTerminatedBlock() {
    restoreState();
    if(!inputStream.isEndOfFileReached()) {
        size_t readBytes;
        size_t currentSize;
        size_t indexOfLastNewline;
        size_t offset = inputBuffer.size();
        size_t notFilledMemorySize = inputBuffer.capacity() - offset;
        char* buffer = inputBuffer.obtainBufferForInput();
        while(true) {
            readBytes = inputStream.read(buffer + offset, notFilledMemorySize);
            if(readBytes < notFilledMemorySize) {
                if(inputStream.isEndOfFileReached()) {
                    buffer[offset + readBytes] = '\n';
                    ++readBytes;
                } else {
                    throw ReaderIOException{};
                }
            }
            currentSize = offset + readBytes;
            inputBuffer.syncSize(currentSize);
            indexOfLastNewline = inputBuffer.getIndexOfLastNewline();
            if(indexOfLastNewline < currentSize) {
                return NewlineBlock{inputBuffer.obtainBufferForInput(), indexOfLastNewline};
            }
            inputBuffer.reserve(chunkSize);
            notFilledMemorySize = chunkSize;
            offset = currentSize;
            buffer = inputBuffer.obtainBufferForInput();
        }
    }
    return NewlineBlock{nullptr, 0};
}