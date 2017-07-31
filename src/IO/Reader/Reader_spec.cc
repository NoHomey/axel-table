#include "Reader.h"
#include "gtest/gtest.h"
#include "../../It/It.h"
#include "../../String/ConstString/ConstString.h"
#include <cstring>


TEST(Reader, Constructor) {
    IT("dose not throw exception when passed nullptr inputStream");

    EXPECT_NO_THROW([]() {
        InputStream inputStream{nullptr};
        Reader reader{inputStream};
    });
}

TEST(Reader, readNewlineBlockThrowsReaderIOException) {
    IT("thows Reader::ReaderIOException when less bytes are read than expected and EOF is not reached");

    class InputStreamStub: public InputStream {
    public:
        InputStreamStub(): InputStream{nullptr} { }

        bool isEndOfFileReached() const noexcept final { return false; }

        size_t read(char*, size_t) final { return 0; }
    };

    InputStreamStub inputStream;

    Reader reader{inputStream};

    EXPECT_THROW(reader.readNewlineBlock(), Reader::ReaderIOException);
}

TEST(Reader, readNewlineBlockWhitEmptyFile) {
    IT("returns NewlineBlock{nullptr, 0} when given empty file");

    class InputStreamStub: public InputStream {
    public:
        InputStreamStub(): InputStream{nullptr} { }

        bool isEndOfFileReached() const noexcept final { return true; }

        size_t read(char*, size_t) final { return 0; }
    };

    InputStreamStub inputStream;

    Reader reader{inputStream};

    Reader::NewlineBlock block = reader.readNewlineBlock();

    EXPECT_EQ(block.size(), 0);

    EXPECT_EQ(block.data(), nullptr);
}

TEST(Reader, readNewlineBlockWithSmallSizeFile) {
    IT("directlly reads the whole file if it has small size");

    class InputStreamStub: public InputStream {
    public:
        InputStreamStub(): InputStream{nullptr}, stubEOF{false} { }

        bool isEndOfFileReached() const noexcept final {
            return stubEOF;
        }

        size_t read(char* buffer, size_t count) final {
            EXPECT_EQ(count, 512);
            std::memcpy(buffer, "This is small file.\nAnd this is small line.\nThis is small paragraph.\nThis is small sentance.\nAnd this is small epilock", 120);

            stubEOF = true;

            return 120;
        }

    private:
        bool stubEOF;
    };

    InputStreamStub inputStream;

    Reader reader{inputStream};

    Reader::NewlineBlock block = reader.readNewlineBlock();

    EXPECT_EQ(block.size(), 120);
    EXPECT_EQ((ConstString{block.data(), block.size()}), (ConstString{"This is small file.\nAnd this is small line.\nThis is small paragraph.\nThis is small sentance.\nAnd this is small epilock", 120}));
}

TEST(Reader, readNewlineBlockWithSingleLineFile) {
    IT("directlly reads the whole file if it is a single line");

    Reader::setInitialSize(32);
    Reader::setChunkSize(16);

    class InputStreamStub: public InputStream {
    public:
        InputStreamStub(): InputStream{nullptr}, reads{0} { }

        bool isEndOfFileReached() const noexcept final {
            return reads == 5;
        }

        size_t read(char* buffer, size_t count) final {
            size_t readCount;
            switch(reads) {
                case 0:
                    EXPECT_EQ(count, 32);
                    std::memcpy(buffer, "Ok so 32 symbols in one line.32 ", 32);
                    readCount = 32;
                    break;
                default:
                    EXPECT_EQ(count, 16);
                    std::memcpy(buffer, "symbols, indeed ", 16);
                    readCount = 16;
            }
            ++reads;
            return readCount;
        }

    private:
        size_t reads;
    };

    InputStreamStub inputStream;

    Reader reader{inputStream};

    Reader::NewlineBlock block = reader.readNewlineBlock();

    EXPECT_EQ(block.size(), 96);
    EXPECT_EQ((ConstString{block.data(), block.size()}), (ConstString{"Ok so 32 symbols in one line.32 symbols, indeed symbols, indeed symbols, indeed symbols, indeed ", 96}));

    block = reader.readNewlineBlock();
    EXPECT_EQ(block.data(), nullptr);
    EXPECT_EQ(block.size(), 0);

    Reader::restoreSizes();
}


TEST(Reader, readNewlineBlock) {
    IT("reads (dummy test)");

    Reader::setInitialSize(4);
    Reader::setChunkSize(2);

    class InputStreamStub: public InputStream {
    public:
        InputStreamStub(): InputStream{nullptr}, reads{0} { }

        bool isEndOfFileReached() const noexcept final {
            return reads == 12;
        }

        size_t read(char* buffer, size_t count) final {
            size_t readCount;
            switch(reads) {
                case 0:
                    EXPECT_EQ(count, 4);
                    std::memcpy(buffer, "This", 4);
                    readCount = 4;
                    break;
                case 1:
                    EXPECT_EQ(count, 2);
                    std::memcpy(buffer, " i", 2);
                    readCount = 2;
                    break;
                case 2:
                    EXPECT_EQ(count, 2);
                    std::memcpy(buffer, "s ", 2);
                    readCount = 2;
                    break;
                case 3:
                    EXPECT_EQ(count, 2);
                    std::memcpy(buffer, "a ", 2);
                    readCount = 2;
                    break;
                case 4:
                    EXPECT_EQ(count, 2);
                    std::memcpy(buffer, "te", 2);
                    readCount = 2;
                    break;
                case 5:
                    EXPECT_EQ(count, 2);
                    std::memcpy(buffer, "st", 2);
                    readCount = 2;
                    break;
                case 6:
                    EXPECT_EQ(count, 2);
                    std::memcpy(buffer, "!!", 2);
                    readCount = 2;
                    break;
                case 7:
                    EXPECT_EQ(count, 2);
                    std::memcpy(buffer, "!\n", 2);
                    readCount = 2;
                    break;
                case 8:
                    EXPECT_EQ(count, 18);
                    std::memcpy(buffer, "And this 2\nThis al", 18);
                    readCount = 18;
                    break;
                case 9:
                    EXPECT_EQ(count, 11);
                    std::memcpy(buffer, "so.\nAnd!!!!", 11);
                    readCount = 11;
                    break;
                case 10:
                    EXPECT_EQ(count, 11);
                    std::memcpy(buffer, " This also\n", 11);
                    readCount = 11;
                    break;
                case 11:
                    EXPECT_EQ(count, 18);
                    std::memcpy(buffer, ".\n\nsome text\n\n?\n", 15);
                    readCount = 15;
                    break;
            }
            ++reads;
            return readCount;
        }

    private:
        size_t reads;
    };

    InputStreamStub inputStream;

    Reader reader{inputStream};

    Reader::NewlineBlock block = reader.readNewlineBlock();
    EXPECT_EQ((ConstString{block.data(), block.size()}), (ConstString{"This is a test!!!", 17}));

    block = reader.readNewlineBlock();
    EXPECT_EQ((ConstString{block.data(), block.size()}), (ConstString{"And this 2", 10}));

    block = reader.readNewlineBlock();
    EXPECT_EQ((ConstString{block.data(), block.size()}), (ConstString{"This also.", 10}));

    block = reader.readNewlineBlock();
    EXPECT_EQ((ConstString{block.data(), block.size()}), (ConstString{"And!!!! This also", 17}));

    block = reader.readNewlineBlock();
    EXPECT_EQ((ConstString{block.data(), block.size()}), (ConstString{".\n\nsome text\n\n?\n", 15}));

    block = reader.readNewlineBlock();
    EXPECT_EQ(block.data(), nullptr);
    EXPECT_EQ(block.size(), 0);

    Reader::restoreSizes();
}