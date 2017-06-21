#include "Table.h"
#include "gtest/gtest.h"
#include "../It/It.h"
#include "../TableCell/EmptyCell/EmptyCell.h"
#include "../TableCell/NumberCell/NumberCell.h"
#include "../TableCell/StringNumberCell/StringNumberCell.h"
#include "../TableCell/StringCell/StringCell.h"
#include "../TableCell/ErrorCell/ErrorCell.h"
#include "../TableCell/CircRefCell/CircRefCell.h"
#include "../TableCell/DivByZeroCell/DivByZeroCell.h"
#include "../TableCell/RootOfNegNumCell/RootOfNegNumCell.h"
#include "../TableCell/ZeroRaisedOnZeroCell/ZeroRaisedOnZeroCell.h"

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

TEST(Table, dataModel) {
    IT("allows editing and geting from fragmented data");
    Table table;

    EXPECT_EQ((&table[{0, 0}]), EmptyCell::obtainPtr());
    NumberCell* numPtr = new NumberCell{9.1}; 
    table.edit({0, 0}, numPtr);
    EXPECT_EQ((&table[{0, 0}]), numPtr);
    EXPECT_DOUBLE_EQ((table[{0, 0}]).getValueAsNumber().getReal(), 9.1);

    NumberCell* numPtr2 = new NumberCell{(const long long)13};
    EXPECT_EQ((&table[{1000, 12340}]), EmptyCell::obtainPtr());
    table.edit({1000, 12340}, numPtr2);
    EXPECT_EQ((&table[{1000, 12340}]), numPtr2);
    EXPECT_EQ((table[{1000, 12340}]).getValueAsNumber().getInteger(), 13);

    const StringNumberCell* strNumPtr = new StringNumberCell{19.41};
    EXPECT_EQ((&table[{1, 0}]), EmptyCell::obtainPtr());
    table.edit({1, 0}, strNumPtr);
    EXPECT_EQ((&table[{1, 0}]), strNumPtr);
    EXPECT_DOUBLE_EQ((table[{1, 0}]).getValueAsNumber().getReal(), 19.41);

    const StringNumberCell* strNumPtr2 = new StringNumberCell{13.42};
    EXPECT_EQ((&table[{0, 1}]), EmptyCell::obtainPtr());
    table.edit({0, 1}, strNumPtr2);
    EXPECT_EQ((&table[{0, 1}]), strNumPtr2);
    EXPECT_DOUBLE_EQ((table[{0, 1}]).getValueAsNumber().getReal(), 13.42);
    
    FixedSizeString str{1};
    str << 'i';
    const StringCell* strPtr = new StringCell{std::move(str)};
    EXPECT_EQ((&table[{3, 5}]), EmptyCell::obtainPtr());
    table.edit({3, 5}, strPtr);
    EXPECT_EQ((&table[{3, 5}]), strPtr);
    EXPECT_DOUBLE_EQ((table[{3, 5}]).getValueAsNumber().getInteger(), 0);

    EXPECT_EQ((&table[{23848, 3429438}]), EmptyCell::obtainPtr());
    table.edit({23848, 3429438}, ErrorCell::obtainPtr());
    EXPECT_EQ((&table[{23848, 3429438}]), ErrorCell::obtainPtr());

    EXPECT_EQ((&table[{0, 2}]), EmptyCell::obtainPtr());
    table.edit({0, 2}, CircRefCell::obtainPtr());
    EXPECT_EQ((&table[{0, 2}]), CircRefCell::obtainPtr());

    EXPECT_EQ((&table[{1, 1}]), EmptyCell::obtainPtr());
    table.edit({1, 1}, DivByZeroCell::obtainPtr());
    EXPECT_EQ((&table[{1, 1}]), DivByZeroCell::obtainPtr());

    EXPECT_EQ((&table[{1, 2}]), EmptyCell::obtainPtr());
    table.edit({1, 2}, RootOfNegNumCell::obtainPtr());
    EXPECT_EQ((&table[{1, 2}]), RootOfNegNumCell::obtainPtr());

    EXPECT_EQ((&table[{5, 6}]), EmptyCell::obtainPtr());
    table.edit({5, 6}, ZeroRaisedOnZeroCell::obtainPtr());
    EXPECT_EQ((&table[{5, 6}]), ZeroRaisedOnZeroCell::obtainPtr());

    EXPECT_EQ((&table[{3434, 3111}]), EmptyCell::obtainPtr());
    table.edit({3434, 3111}, ErrorCell::obtainPtr());
    EXPECT_EQ((&table[{3434, 3111}]), ErrorCell::obtainPtr());

    EXPECT_EQ((&table[{58832, 20381}]), EmptyCell::obtainPtr());
    table.edit({58832, 20381}, EmptyCell::obtainPtr());
    EXPECT_EQ((&table[{58832, 20381}]), EmptyCell::obtainPtr());

    EXPECT_EQ((&table[{897, 798}]), EmptyCell::obtainPtr());
    table.edit({897, 798}, EmptyCell::obtainPtr());
    EXPECT_EQ((&table[{897, 798}]), EmptyCell::obtainPtr());

    for(size_t i = 200; i < 221; ++i) {
        EXPECT_EQ((&table[{i, i}]), EmptyCell::obtainPtr());
        table.edit({i, i}, ErrorCell::obtainPtr());
        EXPECT_EQ((&table[{i, i}]), ErrorCell::obtainPtr());

        EXPECT_EQ((&table[{2 * i, i}]), EmptyCell::obtainPtr());
        table.edit({2 * i, i}, CircRefCell::obtainPtr());
        EXPECT_EQ((&table[{2 * i, i}]), CircRefCell::obtainPtr());

        EXPECT_EQ((&table[{i + 10, i - 10}]), EmptyCell::obtainPtr());
        table.edit({i + 10, i - 10}, DivByZeroCell::obtainPtr());
        EXPECT_EQ((&table[{i + 10, i - 10}]), DivByZeroCell::obtainPtr());

        EXPECT_EQ((&table[{3 * i, 4 * i}]), EmptyCell::obtainPtr());
        table.edit({3 * i, 4 * i}, RootOfNegNumCell::obtainPtr());
        EXPECT_EQ((&table[{3 * i, 4 * i}]), RootOfNegNumCell::obtainPtr());

        EXPECT_EQ((&table[{i + 5, i + 6}]), EmptyCell::obtainPtr());
        table.edit({i + 5, i + 6}, ZeroRaisedOnZeroCell::obtainPtr());
        EXPECT_EQ((&table[{i + 5, i + 6}]), ZeroRaisedOnZeroCell::obtainPtr());

        NumberCell* numPtr = new NumberCell{(const long long)13};
        EXPECT_EQ((&table[{i + 1000, i  + 12340}]), EmptyCell::obtainPtr());
        table.edit({i + 1000, i + 12340}, numPtr);
        EXPECT_EQ((&table[{i + 1000, i + 12340}]), numPtr);
        EXPECT_EQ((table[{i + 1000, i + 12340}]).getValueAsNumber().getInteger(), 13);

        const StringNumberCell* strNumPtr = new StringNumberCell{42.32};
        EXPECT_EQ((&table[{i - 80, i + 1300}]), EmptyCell::obtainPtr());
        table.edit({i - 80, i + 1300}, strNumPtr);
        EXPECT_EQ((&table[{i - 80, i + 1300}]), strNumPtr);
        EXPECT_DOUBLE_EQ((table[{i - 80, i + 1300}]).getValueAsNumber().getReal(), 42.32);

        FixedSizeString str{3};
        str << 'i' << 'v' << 'o';
        const StringCell* strPtr = new StringCell{std::move(str)};
        EXPECT_EQ((&table[{i + 13, i - 5}]), EmptyCell::obtainPtr());
        table.edit({i + 13, i - 5}, strPtr);
        EXPECT_EQ((&table[{i + 13, i - 5}]), strPtr);
        EXPECT_DOUBLE_EQ((table[{i + 13, i - 5}]).getValueAsNumber().getInteger(), 0);
    }
}

TEST(Table, edit) {
    IT("deletes old pointer if it is deletable when editing cell with value");

    class DeleteExpecter: public NumberCell {
    public:
        DeleteExpecter() noexcept: NumberCell{{}} {}

        bool isDeletable() const noexcept final {
            return true;
        }

        ~DeleteExpecter() noexcept {
            EXPECT_TRUE(true);
        }
    };

    class NoDeleteExpecter: public NumberCell {
    public:
        NoDeleteExpecter() noexcept: NumberCell{{}} {}

        bool isDeletable() const noexcept final {
            return false;
        }

        ~NoDeleteExpecter() noexcept {
            EXPECT_TRUE(false);
        }

        bool isDeleted() const noexcept {
            return false;
        }
    };

    Table table;

    for(size_t i = 0; i < 13; ++i) {
        const NumberCell* numPtr = new NumberCell{(long long)i};
        const DeleteExpecter* toBeDeleted = new DeleteExpecter;
        const NoDeleteExpecter* toNotBeDeleted = new NoDeleteExpecter;
        table.edit({i, i * i}, toBeDeleted);
        table.edit({i, i * i}, toNotBeDeleted);
        table.edit({i, i * i}, numPtr);
        EXPECT_FALSE(toNotBeDeleted->isDeleted());
    }
}