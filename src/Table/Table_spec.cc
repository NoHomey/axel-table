#include "Table.h"
#include "gtest/gtest.h"
#include "../It/It.h"
#include "../TableCell/EmptyCell/EmptyCell.h"

TEST(TableIndex, getters) {
    IT("returns the index with which it was created");

    Table::TableIndex index = {9, 42};
    EXPECT_EQ(index.getRow(), 9);
    EXPECT_EQ(index.getColumn(), 42);

    Table::TableIndex index2 = {22, 2};
    EXPECT_EQ(index2.getRow(), 22);
    EXPECT_EQ(index2.getColumn(), 2);

    Table::TableIndex index3 = {333, 99};
    EXPECT_EQ(index3.getRow(), 333);
    EXPECT_EQ(index3.getColumn(), 99);

    Table::TableIndex index4 = {193934, 234234};
    EXPECT_EQ(index4.getRow(), 193934);
    EXPECT_EQ(index4.getColumn(), 234234);
}

TEST(Table, indexOperator) {
    IT("can get any indexable cell in \"virtually\" continuous table, if there is no real cell it will return EmptyCell");
    Table table;
    Table::TableIndex index[] = {{0, 0}, {0, 10000}, {100, 9999}, {500, 200}, {300, 3333333}, {1, 2}, {9, 13944985}};
    for(size_t i = 0; i < 7; ++i) {
        const size_t row = index[i].getRow();
        const size_t col = index[i].getColumn();
        EXPECT_EQ((&table[index[i]]), EmptyCell::obtainPtr());
        EXPECT_EQ((&table[{col, row}]), EmptyCell::obtainPtr());
        EXPECT_EQ((&table[{2 * col, 2 * row}]), EmptyCell::obtainPtr());
        EXPECT_EQ((&table[{2 * row, 2 * col}]), EmptyCell::obtainPtr());
        EXPECT_EQ((&table[{3 * col, 3 * row}]), EmptyCell::obtainPtr());
        EXPECT_EQ((&table[{3 * row, 3 * col}]), EmptyCell::obtainPtr());
    }
}