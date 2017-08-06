#include "TableCell.h"
#include "gtest/gtest.h"
#include "../It/It.h"

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

TEST(TableCell, deleteIfDeletableWhenDeletable) {
    IT("deletes the pointer if it is deletable");

    Deletable* d = new Deletable{};
    EXPECT_FALSE(Deletable::isDeleted());
    TableCell::deleteIfDeletable(d);
    EXPECT_TRUE(Deletable::isDeleted());

    d = new Deletable{};
    EXPECT_FALSE(Deletable::isDeleted());
    TableCell::deleteIfDeletable(d);
    EXPECT_TRUE(Deletable::isDeleted());

    d = new Deletable{};
    EXPECT_FALSE(Deletable::isDeleted());
    TableCell::deleteIfDeletable(d);
    EXPECT_TRUE(Deletable::isDeleted());
}

class NotDeletable: public TableCell {
public:
    static bool isDeleted() noexcept {
        return deleted;
    }

    ~NotDeletable() noexcept { deleted = true; }

    const Number& getValueAsNumber() const { return Number::getAdditionNeutralElement(); }

    size_t calculateOutputLength() const noexcept { return 0; }

    size_t calculateSerializedLength() const noexcept { return 0; }

    bool isDeletable() const noexcept { return false; }

    private: static bool deleted;
};

bool NotDeletable::deleted = false;

TEST(TableCell, deleteIfDeletableWhenNotDeletable) {
    IT("dose nothing");

    NotDeletable d = NotDeletable{};
    EXPECT_FALSE(NotDeletable::isDeleted());
    TableCell::deleteIfDeletable(&d);
    EXPECT_FALSE(NotDeletable::isDeleted());
    TableCell::deleteIfDeletable(&d);
    EXPECT_FALSE(NotDeletable::isDeleted());
}