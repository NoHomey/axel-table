#include "Reader.h"
#include "gtest/gtest.h"
#include "../../It/It.h"

TEST(Reader, Constructor) {
    IT("dose not throw exception when passed nullptr inputStream");

    EXPECT_NO_THROW([]() {
        InputStream inputStream{nullptr};
        Reader reader{inputStream};
    });
}

TEST(Reader, readNewlineTerminatedBlockThrowsReaderIOException) {
    IT("thows Reader::ReaderIOException when less bytes are read than expected and EOF is not reached");

    class InputStreamStub: public InputStream {
    public:
        InputStreamStub(): InputStream{nullptr} { }

        bool isEndOfFileReached() const noexcept final { return false; }

        size_t read(char*, size_t) final { return 0; }
    };

    InputStreamStub inputStream;

    Reader reader{inputStream};

    EXPECT_THROW(reader.readNewlineTerminatedBlock(), Reader::ReaderIOException);
}

TEST(Reader, readNewlineTerminatedBlockWhitEmptyFile) {
    IT("returns NewlineBlock{nullptr, 0} when given empty file");

    class InputStreamStub: public InputStream {
    public:
        InputStreamStub(): InputStream{nullptr} { }

        bool isEndOfFileReached() const noexcept final { return true; }

        size_t read(char*, size_t) final { return 0; }
    };

    InputStreamStub inputStream;

    Reader reader{inputStream};

    Reader::NewlineBlock block = reader.readNewlineTerminatedBlock();

    EXPECT_EQ(block.size(), 0);

    EXPECT_EQ(block.data(), nullptr);
}

TEST(Reader, readNewlineTerminatedBlockWithSmallSizeFile) {
    IT("directlly reads the whole file if it has small size");

    class InputStreamStub: public InputStream {
    public:
        InputStreamStub(): InputStream{nullptr}, stubEOF{false} { }

        bool isEndOfFileReached() const noexcept final {
            return stubEOF;
        }

        size_t read(char* buffer, size_t count) final {
            EXPECT_EQ(count, 512);
            buffer[0] = 'i';
            buffer[1] = 'v';
            buffer[2] = 'o';

            stubEOF = true;

            return 3;
        }

    private:
        bool stubEOF;
    };

    InputStreamStub inputStream;

    Reader reader{inputStream};

    Reader::NewlineBlock block = reader.readNewlineTerminatedBlock();

    EXPECT_EQ(block.size(), 3);

    const char* data = block.data();

    EXPECT_EQ(data[0], 'i');
    EXPECT_EQ(data[1], 'v');
    EXPECT_EQ(data[2], 'o');
}