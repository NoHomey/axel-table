#include "StringCell.h"
#include "gtest/gtest.h"
#include "../../It/It.h"

class StringCellTest: public ::testing::Test {
public:
    StringCellTest():
    cell1{std::move(str1())},
    cell2{std::move(str2())},
    cell3{std::move(str3())},
    cell4{std::move(str4())},
    cell5{std::move(str5())},
    cell6{std::move(str6())},
    cell7{std::move(str7())},
    cell8{std::move(str8())},
    cell9{std::move(FixedSizeString{0})}
    { }

protected:
    StringCell cell1;
    StringCell cell2;
    StringCell cell3;
    StringCell cell4;
    StringCell cell5;
    StringCell cell6;
    StringCell cell7;
    StringCell cell8;
    StringCell cell9;

private:
    static FixedSizeString str1() {
        FixedSizeString str{9};
        str << 's' << 'o' << 'm' << 'e' << ' ' << 't' << 'e' << 'x' << 't';
        return str;
    }

    static FixedSizeString str2() {
        FixedSizeString str{4};
        str << '@' << '#' << '$' << '%';
        return str;
    }

    static FixedSizeString str3() {
        FixedSizeString str{12};
        str << 'H' << 'e' << 'l' << 'l' << 'o' << ' ' << 'w' << 'o' << 'r' << 'l' << 'd' << '!';
        return str;
    }

    static FixedSizeString str4() {
        FixedSizeString str{4};
        str << 'a' << '\\' << 's' << 'd';
        return str;
    }
    
    static FixedSizeString str5() {
        FixedSizeString str{6};
        str << '1' << '\\' << '2' << '"' << '3' << '\\';
        return str;
    }

    static FixedSizeString str6() {
        FixedSizeString str{6};
        str << '|' << '\\' << '\"' << '\\' << '"' << '|';
        return str;
    }

    static FixedSizeString str7() {
        FixedSizeString str{7};
        str << '"' << 'q' << 'u' << 'o' << 't' << 'e' << '"';
        return str;
    }

    static FixedSizeString str8() {
        FixedSizeString str{16};
        str << 'e' << '\\' << '"' << 's' << '\\' << 'c' << '"' << 'a' << 'p' << 'e' << '\\' << '\\' << '\\' << 'i' << 't' << '!';
        return str;
    }
};

TEST(StringCel, Dynamics) {
    FixedSizeString str{0};
    const TableCell* ptr = new StringCell{std::move(str)};
    delete ptr;
}

TEST_F(StringCellTest, getValueAsNumber) {
    IT("constantly return Number instance with Value integer 0");
    EXPECT_EQ(cell1.getValueAsNumber().getInteger(), 0);
    EXPECT_EQ(cell2.getValueAsNumber().getInteger(), 0);
    EXPECT_EQ(cell3.getValueAsNumber().getInteger(), 0);
    EXPECT_EQ(cell4.getValueAsNumber().getInteger(), 0);
    EXPECT_EQ(cell5.getValueAsNumber().getInteger(), 0);
    EXPECT_EQ(cell6.getValueAsNumber().getInteger(), 0);
    EXPECT_EQ(cell7.getValueAsNumber().getInteger(), 0);
    EXPECT_EQ(cell8.getValueAsNumber().getInteger(), 0);
    EXPECT_EQ(cell9.getValueAsNumber().getInteger(), 0);
}

TEST_F(StringCellTest, calculateOutputLength) {
    IT("returns the same number as the string value's length");
    EXPECT_EQ(cell1.calculateOutputLength(), 9);
    EXPECT_EQ(cell2.calculateOutputLength(), 4);
    EXPECT_EQ(cell3.calculateOutputLength(), 12);
    EXPECT_EQ(cell4.calculateOutputLength(), 4);
    EXPECT_EQ(cell5.calculateOutputLength(), 6);
    EXPECT_EQ(cell6.calculateOutputLength(), 6);
    EXPECT_EQ(cell7.calculateOutputLength(), 7);
    EXPECT_EQ(cell8.calculateOutputLength(), 16);
    EXPECT_EQ(cell9.calculateOutputLength(), 0);
}

TEST_F(StringCellTest, calculateSerializedLength) {
    IT("returns the same number as the string value's length");
    EXPECT_EQ(cell1.calculateSerializedLength(), 11);
    EXPECT_EQ(cell2.calculateSerializedLength(), 6);
    EXPECT_EQ(cell3.calculateSerializedLength(), 14);
    EXPECT_EQ(cell4.calculateSerializedLength(), 7);
    EXPECT_EQ(cell5.calculateSerializedLength(), 11);
    EXPECT_EQ(cell6.calculateSerializedLength(), 12);
    EXPECT_EQ(cell7.calculateSerializedLength(), 11);
    EXPECT_EQ(cell8.calculateSerializedLength(), 25);
    EXPECT_EQ(cell9.calculateSerializedLength(), 2);
}

TEST_F(StringCellTest, isDeletable) {
    IT("returns true");
    EXPECT_TRUE(cell1.isDeletable());
    EXPECT_TRUE(cell2.isDeletable());
    EXPECT_TRUE(cell3.isDeletable());
    EXPECT_TRUE(cell4.isDeletable());
    EXPECT_TRUE(cell5.isDeletable());
    EXPECT_TRUE(cell6.isDeletable());
    EXPECT_TRUE(cell7.isDeletable());
    EXPECT_TRUE(cell8.isDeletable());
    EXPECT_TRUE(cell9.isDeletable());
}