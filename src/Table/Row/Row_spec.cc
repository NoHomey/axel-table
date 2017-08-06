#include "Row.h"
#include "gtest/gtest.h"
#include "../../It/It.h"
#include "../../TableCell/EmptyCell/EmptyCell.h"
#include "../../TableCell/NumberCell/NumberCell.h"
#include "../../TableCell/StringNumberCell/StringNumberCell.h"
#include "../../TableCell/StringCell/StringCell.h"
#include "../../TableCell/ErrorCell/ErrorCell.h"
#include "../../TableCell/CircRefCell/CircRefCell.h"
#include "../../TableCell/DivByZeroCell/DivByZeroCell.h"
#include "../../TableCell/RootOfNegNumCell/RootOfNegNumCell.h"
#include "../../TableCell/ZeroRaisedOnZeroCell/ZeroRaisedOnZeroCell.h"

TEST(Row, cellAtWhenEmpty) {
    IT("should has zero length and cellAt should return EmptyCell ptr");

    Row row;

    EXPECT_EQ(row.length(), 0);

    for(size_t i = 0; i < 100; ++i) {
        EXPECT_TRUE(EmptyCell::isEmptyCell(row.cellAt(i)));
        EXPECT_TRUE(EmptyCell::isEmptyCell(row.cellAt(i * i)));
        EXPECT_TRUE(EmptyCell::isEmptyCell(row.cellAt(2 * i)));
        EXPECT_TRUE(EmptyCell::isEmptyCell(row.cellAt(i * i + i)));
        EXPECT_TRUE(EmptyCell::isEmptyCell(row.cellAt(i * 100 + i)));
        EXPECT_TRUE(EmptyCell::isEmptyCell(row.cellAt(i * i * i)));
        EXPECT_TRUE(EmptyCell::isEmptyCell(row.cellAt(i * 1000 + 3 * i * i + i)));
        EXPECT_EQ(row.length(), 0);
        EXPECT_EQ(row.getCells().size(), 0);
    }

    EXPECT_EQ(row.length(), 0);
    EXPECT_EQ(row.getCells().size(), 0);
}

TEST(Row, editWithEmptyCell) {
    IT("should not change size (fill cell) if editing with EmptyCell");

    Row row;

    EXPECT_EQ(row.length(), 0);

    for(size_t i = 0; i < 100; ++i) {
        row.edit(i, EmptyCell::obtainPtr());
        row.edit(i * i, EmptyCell::obtainPtr());
        row.edit(2 * i, EmptyCell::obtainPtr());
        row.edit(i * i + i, EmptyCell::obtainPtr());
        row.edit(i * 100 + i, EmptyCell::obtainPtr());
        row.edit(i * i * i, EmptyCell::obtainPtr());
        row.edit(i * 1000 + 3 * i * i + i, EmptyCell::obtainPtr());

        EXPECT_TRUE(EmptyCell::isEmptyCell(row.cellAt(i)));
        EXPECT_TRUE(EmptyCell::isEmptyCell(row.cellAt(i * i)));
        EXPECT_TRUE(EmptyCell::isEmptyCell(row.cellAt(2 * i)));
        EXPECT_TRUE(EmptyCell::isEmptyCell(row.cellAt(i * i + i)));
        EXPECT_TRUE(EmptyCell::isEmptyCell(row.cellAt(i * 100 + i)));
        EXPECT_TRUE(EmptyCell::isEmptyCell(row.cellAt(i * i * i)));
        EXPECT_TRUE(EmptyCell::isEmptyCell(row.cellAt(i * 1000 + 3 * i * i + i)));
        EXPECT_EQ(row.length(), 0);
        EXPECT_EQ(row.getCells().size(), 0);
    }
    
    EXPECT_EQ(row.length(), 0);
    EXPECT_EQ(row.getCells().size(), 0);
}

TEST(Row, editWithNoneEmptyCell) {
    IT("should edit cells adding new cell if the cell is empty or change it to the provided none EmptyCell");

    Row row;

    EXPECT_EQ(row.length(), 0);

    for(size_t i = 0; i < 100; ++i) {
        row.edit(i, ErrorCell::obtainPtr());
        EXPECT_EQ(row.cellAt(i), ErrorCell::obtainPtr());

        row.edit(i * i, CircRefCell::obtainPtr());
        EXPECT_EQ(row.cellAt(i * i), CircRefCell::obtainPtr());

        row.edit(2 * i, DivByZeroCell::obtainPtr());
        EXPECT_EQ(row.cellAt(2 * i), DivByZeroCell::obtainPtr());

        row.edit(i * i + i, RootOfNegNumCell::obtainPtr());
        EXPECT_EQ(row.cellAt(i * i + i), RootOfNegNumCell::obtainPtr());

        row.edit(i * 100 + i, ZeroRaisedOnZeroCell::obtainPtr());
        EXPECT_EQ(row.cellAt(i * 100 + i), ZeroRaisedOnZeroCell::obtainPtr());

        NumberCell* numCell = new NumberCell{3.14};
        row.edit(i * i * i, numCell);
        EXPECT_EQ(row.cellAt(i * i * i), numCell);

        StringNumberCell* strNumCell = new StringNumberCell{3.14};
        row.edit(i * i * 1000 + 3 * i * i + i, strNumCell);

        EXPECT_FALSE(EmptyCell::isEmptyCell(row.cellAt(i)));
        EXPECT_FALSE(EmptyCell::isEmptyCell(row.cellAt(i * i)));
        EXPECT_FALSE(EmptyCell::isEmptyCell(row.cellAt(2 * i)));
        EXPECT_FALSE(EmptyCell::isEmptyCell(row.cellAt(i * i + i)));
        EXPECT_FALSE(EmptyCell::isEmptyCell(row.cellAt(i * 100 + i)));
        EXPECT_FALSE(EmptyCell::isEmptyCell(row.cellAt(i * i * i)));
        EXPECT_FALSE(EmptyCell::isEmptyCell(row.cellAt(i * i * 1000 + 3 * i * i + i)));
        
        EXPECT_EQ(row.length(), i * i * 1000 + 3 * i * i + i + 1);
        EXPECT_TRUE(row.getCells().size() >= 4 * i + 1 && row.getCells().size() <= 7 * i + 1);
    }
    
    EXPECT_EQ(row.length(), 9830503);
    EXPECT_EQ(row.getCells().size(), 614);
}

class Deletable: public TableCell {
public:
    static bool isDeleted() noexcept {
        return deleted;
    }

    Deletable() { deleted = false; }

    ~Deletable() noexcept { deleted = true; }

    const Number& getValueAsNumber() const { return Number::getAdditionNeutralElement(); }

    size_t calculateOutputLength() const noexcept { return 0; }

    size_t calculateSerializedLength() const noexcept { return 0; }

    bool isDeletable() const noexcept { return true; }

    private: static bool deleted;
};

bool Deletable::deleted = false;

TEST(Row, editWhenEditingNoneEmptyCellWithEmptyCell) {
    IT("should remove and delete the none EmptyCell when overwriting it with EmptyCell");

    Row row;

    EXPECT_EQ(row.length(), 0);
    EXPECT_EQ(row.getCells().size(), 0);

    Deletable* d;
    size_t cell;

    size_t cells[] = {3, 12, 34, 3459, 34827, 3294, 1231, 343454, 99349, 99, 129583};

    for(int i  = 0; i < 10; ++i) {
        d = new Deletable{};
        cell = cells[i];
        row.edit(cell, d);
        EXPECT_EQ(row.cellAt(cell), d);
        EXPECT_EQ(row.length(), cell + 1);
        EXPECT_EQ(row.getCells().size(), 1);

        EXPECT_FALSE(Deletable::isDeleted());
        row.edit(cell, EmptyCell::obtainPtr());
        EXPECT_EQ(row.cellAt(cell), EmptyCell::obtainPtr());
        EXPECT_TRUE(Deletable::isDeleted());
        EXPECT_EQ(row.length(), 0);
        EXPECT_EQ(row.getCells().size(), 0);
    }
}

class Deletable2: public TableCell {
public:
    static bool isDeleted() noexcept {
        return deleted;
    }

    Deletable2() { deleted = false; }

    ~Deletable2() noexcept { deleted = true; }

    const Number& getValueAsNumber() const { return Number::getAdditionNeutralElement(); }

    size_t calculateOutputLength() const noexcept { return 0; }

    size_t calculateSerializedLength() const noexcept { return 0; }

    bool isDeletable() const noexcept { return true; }

    private: static bool deleted;
};

bool Deletable2::deleted = false;

TEST(Row, editDeleting) {
    IT("should remove and delete cell when editing a cell");

    Row row;

    EXPECT_EQ(row.length(), 0);
    EXPECT_EQ(row.getCells().size(), 0);

    Deletable* d;
    Deletable2* d2;
    size_t cell;

    size_t cells[] = {3, 12, 34, 3459, 34827, 3294, 1231, 343454, 99349, 99, 129583};

    for(int i  = 0; i < 10; ++i) {
        d = new Deletable{};
        d2 = new Deletable2{};
        cell = cells[i];
        row.edit(cell, d);
        EXPECT_EQ(row.cellAt(cell), d);
        EXPECT_EQ(row.length(), cell + 1);
        EXPECT_EQ(row.getCells().size(), 1);

        EXPECT_FALSE(Deletable::isDeleted());
        row.edit(cell, d2);
        EXPECT_EQ(row.cellAt(cell), d2);
        EXPECT_TRUE(Deletable::isDeleted());
        EXPECT_EQ(row.length(), cell + 1);
        EXPECT_EQ(row.getCells().size(), 1);

        EXPECT_FALSE(Deletable2::isDeleted());
        row.edit(cell, EmptyCell::obtainPtr());
        EXPECT_EQ(row.cellAt(cell), EmptyCell::obtainPtr());
        EXPECT_TRUE(Deletable2::isDeleted());
        EXPECT_EQ(row.length(), 0);
        EXPECT_EQ(row.getCells().size(), 0);
    }
}

class DeletableCell: public TableCell {
public:
    static const bool* deleted() noexcept {
        return cells;
    }

    DeletableCell(unsigned char id): index{id} { }

    ~DeletableCell() noexcept { cells[index] = true; }

    const Number& getValueAsNumber() const { return Number::getAdditionNeutralElement(); }

    size_t calculateOutputLength() const noexcept { return 0; }

    size_t calculateSerializedLength() const noexcept { return 0; }

    bool isDeletable() const noexcept { return true; }

private:
    unsigned char index;

    static bool cells[10];
};

bool DeletableCell::cells[10] = {false, };

TEST(Row, Destructor) {
    IT("should delete all cells when destructed");
    {
        Row row;

        const DeletableCell* d = new DeletableCell{0};
        row.edit(10, d);
        EXPECT_EQ(row.cellAt(10), d);
        EXPECT_EQ(row.length(), 11);
        EXPECT_EQ(row.getCells().size(), 1);

        EXPECT_FALSE(DeletableCell::deleted()[0]);
        d = new DeletableCell{1};
        row.edit(10, d);
        EXPECT_EQ(row.cellAt(10), d);
        EXPECT_TRUE(DeletableCell::deleted()[0]);
        EXPECT_EQ(row.length(), 11);
        EXPECT_EQ(row.getCells().size(), 1);

        const DeletableCell* c = new DeletableCell{2};
        row.edit(10812, c);
        EXPECT_EQ(row.cellAt(10812), c);
        EXPECT_EQ(row.length(), 10813);
        EXPECT_EQ(row.getCells().size(), 2);

        const DeletableCell* c3 = new DeletableCell{3};
        row.edit(9163, c3);
        EXPECT_EQ(row.cellAt(9163), c3);
        EXPECT_EQ(row.length(), 10813);
        EXPECT_EQ(row.getCells().size(), 3);

        EXPECT_FALSE(DeletableCell::deleted()[2]);
        d = new DeletableCell{4};
        row.edit(10812, d);
        EXPECT_EQ(row.cellAt(10812), d);
        EXPECT_TRUE(DeletableCell::deleted()[2]);
        EXPECT_EQ(row.length(), 10813);
        EXPECT_EQ(row.getCells().size(), 3);

        EXPECT_FALSE(DeletableCell::deleted()[4]);
        d = new DeletableCell{5};
        row.edit(10812, d);
        EXPECT_EQ(row.cellAt(10812), d);
        EXPECT_TRUE(DeletableCell::deleted()[4]);
        EXPECT_EQ(row.length(), 10813);
        EXPECT_EQ(row.getCells().size(), 3);

        EXPECT_FALSE(DeletableCell::deleted()[3]);
        d = new DeletableCell{6};
        row.edit(9163, d);
        EXPECT_EQ(row.cellAt(9163), d);
        EXPECT_TRUE(DeletableCell::deleted()[3]);
        EXPECT_EQ(row.length(), 10813);
        EXPECT_EQ(row.getCells().size(), 3);

        EXPECT_FALSE(DeletableCell::deleted()[5]);
        row.edit(10812, EmptyCell::obtainPtr());
        EXPECT_EQ(row.cellAt(10812), EmptyCell::obtainPtr());
        EXPECT_TRUE(DeletableCell::deleted()[5]);
        EXPECT_EQ(row.length(), 9164);
        EXPECT_EQ(row.getCells().size(), 2);

        d = new DeletableCell{7};
        row.edit(333, d);
        EXPECT_EQ(row.length(), 9164);
        EXPECT_EQ(row.getCells().size(), 3);

        d = new DeletableCell{8};
        row.edit(3331, d);
        EXPECT_EQ(row.length(), 9164);
        EXPECT_EQ(row.getCells().size(), 4);

        d = new DeletableCell{9};
        row.edit(75830, d);
        EXPECT_EQ(row.length(), 75831);
        EXPECT_EQ(row.getCells().size(), 5);

        EXPECT_FALSE(DeletableCell::deleted()[7]);
        row.edit(333, EmptyCell::obtainPtr());
        EXPECT_TRUE(DeletableCell::deleted()[7]);
        EXPECT_EQ(row.length(), 75831);
        EXPECT_EQ(row.getCells().size(), 4);

        EXPECT_FALSE(DeletableCell::deleted()[1]);
        EXPECT_FALSE(DeletableCell::deleted()[6]);
        EXPECT_FALSE(DeletableCell::deleted()[8]);
        EXPECT_FALSE(DeletableCell::deleted()[9]);
    }

    const bool* deleted = DeletableCell::deleted();

    for(size_t i = 0; i < 10; ++i) {
        EXPECT_TRUE(deleted[i]);
    }
}