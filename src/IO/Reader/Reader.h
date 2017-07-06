#pragma once

#include "../InputBuffer/InputBuffer.h"
#include "../InputStream/InputStream.h"

class Reader {
public:
    class ReaderIOException: public Exception { };

    class NewlineBlock {
    public:
        NewlineBlock(const char* blockData, size_t sizeInBytes) noexcept;

        const char* data() const noexcept;

        size_t size() const noexcept;

    private:
        const char* block;
        size_t blockSize;
    };

    Reader(InputStream& iStream) noexcept;

    MOCKABLE NewlineBlock readNewlineTerminatedBlock();

protected:
    InputStream& inputStream;
    InputBuffer inputBuffer;

private:
    void restoreState() noexcept;

    static const size_t initialSize = 4096;

    static const size_t chunkSize = 256;
};