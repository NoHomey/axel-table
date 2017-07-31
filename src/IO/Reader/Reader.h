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

    MOCKABLE ~Reader() noexcept = default;

    MOCKABLE NewlineBlock readNewlineBlock();

#ifdef __TEST__

    static void setInitialSize(size_t initialSize) noexcept {
        Reader::initialSize = initialSize;
    }

    static void setChunkSize(size_t chunkSize) noexcept {
        Reader::chunkSize = chunkSize;
    }

    static void restoreSizes() noexcept {
        Reader::initialSize = 512;

        Reader::chunkSize = 256;
    }
    
#endif

protected:
    InputStream& inputStream;
    InputBuffer inputBuffer;

private:
    void restoreState() noexcept;

    static MOCKABLE_CONST size_t initialSize;

    static MOCKABLE_CONST size_t chunkSize;
};