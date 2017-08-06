#include "TableParser.h"
#include "gtest/gtest.h"
#include "../../It/It.h"
#include "../../TableCell/EmptyCell/EmptyCell.h"
#include <cstring>

class InputStreamStub: public InputStream {
public:
    InputStreamStub(const char* data, size_t length)
    : InputStream{nullptr}, data{data}, length{length}, stubEOF{false} { }

    bool isEndOfFileReached() const noexcept final {
        return stubEOF;
    }

    size_t read(char* buffer, size_t) final {
        std::memcpy(buffer, data, length);

        stubEOF = true;

        return length;
    }

private:
    const char* data;
    size_t length;
    bool stubEOF;
};

TEST(TableParser, test) {

    InputStreamStub stream{"123, 362819, -12597032,,  ,1\n   123.5,    3.14   \n    \"112\" , \"text\\\"more\", \"\\\"\"", 80};
    Reader reader{stream};
    TableParser parser{reader};

    Table table = std::move(parser.parse());

    EXPECT_EQ(table.getRowsCount(), 3);
    EXPECT_EQ(table.getColumnsCount(), 6);

    EXPECT_EQ((table[{0, 0}])->getValueAsNumber().getInteger(), 123);
    EXPECT_EQ((table[{0, 1}])->getValueAsNumber().getInteger(), 362819);
    EXPECT_EQ((table[{0, 2}])->getValueAsNumber().getInteger(), -12597032);
    EXPECT_TRUE(EmptyCell::isEmptyCell(table[{0, 3}]));
    EXPECT_TRUE(EmptyCell::isEmptyCell(table[{0, 4}]));
    EXPECT_EQ((table[{0, 5}])->getValueAsNumber().getInteger(), 1);
    EXPECT_TRUE(EmptyCell::isEmptyCell(table[{0, 6}]));
    EXPECT_DOUBLE_EQ((table[{1, 0}])->getValueAsNumber().getReal(), 123.5);
    EXPECT_DOUBLE_EQ((table[{1, 1}])->getValueAsNumber().getReal(), 3.14);
    EXPECT_TRUE(EmptyCell::isEmptyCell(table[{1, 2}]));
    EXPECT_EQ((table[{2, 0}])->getValueAsNumber().getInteger(), 112);
    EXPECT_EQ((table[{2, 1}])->getValueAsNumber().getInteger(), 0);
    EXPECT_EQ((table[{2, 1}])->calculateOutputLength(), 9);
    EXPECT_EQ((table[{2, 1}])->calculateSerializedLength(), 12);
    EXPECT_EQ((table[{2, 2}])->getValueAsNumber().getInteger(), 0);
    EXPECT_EQ((table[{2, 2}])->calculateOutputLength(), 1);
    EXPECT_EQ((table[{2, 2}])->calculateSerializedLength(), 4);
    EXPECT_TRUE(EmptyCell::isEmptyCell(table[{2, 3}]));
}