#include "FragmentedDynamicArray.htd"
#include "gtest/gtest.h"
#include "../../It/It.h"

using TestArray = FragmentedDynamicArray<int>;

TEST(FragmentedDynamicArray, DefaultConstructor) {
    IT("should create empty FragmentedDynamicArray with no capacity");
    TestArray array;
    EXPECT_TRUE(array.isEmpty());
    EXPECT_EQ(array.size(), 0);
    EXPECT_EQ(array.capacity(), 0);
    EXPECT_TRUE(array.isFull());
}

TEST(FragmentedDynamicArray, SizeConstructor) {
    IT("should create empty FragmentedDynamicArray with capacity equal to provided size");
    TestArray array{9};
    EXPECT_TRUE(array.isEmpty());
    EXPECT_EQ(array.size(), 0);
    EXPECT_EQ(array.capacity(), 9);
    EXPECT_FALSE(array.isFull());
    TestArray empty{0};
    EXPECT_TRUE(empty.isEmpty());
    EXPECT_EQ(empty.size(), 0);
    EXPECT_EQ(empty.capacity(), 0);
    EXPECT_TRUE(empty.isFull());
}

TEST(FragmentedDynamicArray, isEmpty) {
    IT("returns true if FragmentedDynamicArray's size is equal to 0");
    TestArray array;
    EXPECT_TRUE(array.isEmpty());
    array.addElement(9);
    EXPECT_FALSE(array.isEmpty());
}

TEST(FragmentedDynamicArray, isFull) {
    IT("returns true if FragmentedDynamicArray's size is equal to it's capacity");
    TestArray array;
    EXPECT_TRUE(array.isFull());
    array.addElement(9);
    EXPECT_FALSE(array.isFull());
    EXPECT_EQ(array.size(), 1);
    EXPECT_EQ(array.capacity(), 2);
    array.addElement(3);
    EXPECT_TRUE(array.isFull());
    EXPECT_EQ(array.size(), 2);
    EXPECT_EQ(array.capacity(), 2);
}

TEST(FragmentedDynamicArray, size) {
    IT("returns the count of elements in the FragmentedDynamicArray");
    TestArray array;
    EXPECT_EQ(array.size(), 0);
    array.addElement(9);
    EXPECT_EQ(array.size(), 1);
    array.addElement(4);
    EXPECT_EQ(array.size(), 2);
    for(size_t i = 0; i < 9; ++i) {
        array.addElement(i);
    }
    EXPECT_EQ(array.size(), 11);
    array.addElement(12, 100);
    EXPECT_EQ(array.size(), 12);
    array.addElement(-100, 10000);
    EXPECT_EQ(array.size(), 13);
    array.addElement(-10000, 14546);
    EXPECT_EQ(array.size(), 14);
    array.addElement(1, 14);
    EXPECT_EQ(array.size(), 15);
}

TEST(FragmentedDynamicArray, capacity) {
    IT("returns the size of dynamically allocated memory for the FragmentedDynamicArray's elements");
    TestArray array;
    EXPECT_EQ(array.capacity(), 0);
    array.addElement(9);
    EXPECT_EQ(array.capacity(), 2);
    array.addElement(4);
    EXPECT_EQ(array.capacity(), 2);
    for(size_t i = 0; i < 9; ++i) {
        array.addElement(i);
    }
    EXPECT_EQ(array.capacity(), 14);
    array.addElement(12, 100);
    EXPECT_EQ(array.capacity(), 16);
    array.addElement(-100, 10000);
    EXPECT_EQ(array.capacity(), 16);
    array.addElement(-10000, 14546);
    EXPECT_EQ(array.capacity(), 20);
    array.addElement(1, 14);
    EXPECT_EQ(array.capacity(), 20);
}

TEST(FragmentedDynamicArray, addElementWithoutIndex) {
    IT("adds new element to the FragmentedDynamicArray if it is full it will also resize it to capacity equal to [2 x size]");
    TestArray array;
    array.addElement(9);
    EXPECT_FALSE(array.isEmpty());
    EXPECT_EQ(array.size(), 1);
    EXPECT_EQ(array.capacity(), 2);
    EXPECT_FALSE(array.isFull());
    for(size_t i = 0; i < 13; ++i) {
        array.addElement(i);
    }
    EXPECT_FALSE(array.isEmpty());
    EXPECT_EQ(array.size(), 14);
    EXPECT_EQ(array.capacity(), 14);
    EXPECT_TRUE(array.isFull());
    for(size_t i = 42; i < 47; ++i) {
        array.addElement(i);
    }
    EXPECT_FALSE(array.isEmpty());
    EXPECT_EQ(array.size(), 19);
    EXPECT_EQ(array.capacity(), 30);
    EXPECT_FALSE(array.isFull());
    array.addElement(22);
    EXPECT_EQ(array.size(), 20);
    EXPECT_EQ(array.capacity(), 30);
    EXPECT_FALSE(array.isFull());
    array.addElement(23);
    EXPECT_EQ(array.size(), 21);
    EXPECT_EQ(array.capacity(), 30);
    EXPECT_FALSE(array.isFull());
}

TEST(FragmentedDynamicArray, CopyConstructor) {
    IT("should copy other FragmentedDynamicArray and sets capacity and size of the copy equal to other's size");
    TestArray empty;
    TestArray array = empty;
    EXPECT_TRUE(array.isEmpty());
    EXPECT_EQ(array.size(), 0);
    EXPECT_EQ(array.capacity(), 0);
    EXPECT_TRUE(array.isFull());
    array.addElement(2);
    array.addElement(9);
    array.addElement(7);
    EXPECT_FALSE(array.isEmpty());
    EXPECT_EQ(array.size(), 3);
    EXPECT_EQ(array.capacity(), 6);
    EXPECT_FALSE(array.isFull());
    TestArray copy = array;
    EXPECT_FALSE(copy.isEmpty());
    EXPECT_EQ(copy.size(), 3);
    EXPECT_EQ(copy.capacity(), 3);
    EXPECT_TRUE(copy.isFull());
    EXPECT_EQ(copy[0], 2);
    EXPECT_EQ(copy[1], 9);
    EXPECT_EQ(copy[2], 7);
    copy.addElement(-10, 3944);
    copy.addElement(100, 10000);
    EXPECT_FALSE(copy.isEmpty());
    EXPECT_EQ(copy.size(), 5);
    EXPECT_EQ(copy.capacity(), 5);
    EXPECT_TRUE(copy.isFull());
    copy.addElement(99, 99);
    EXPECT_EQ(copy.size(), 6);
    EXPECT_EQ(copy.capacity(), 9);
    EXPECT_FALSE(copy.isFull());
    TestArray copyOfCopy = copy;
    EXPECT_EQ(copyOfCopy.size(), 6);
    EXPECT_EQ(copyOfCopy.capacity(), 6);
    EXPECT_TRUE(copyOfCopy.isFull());
    EXPECT_EQ(copyOfCopy[0], 2);
    EXPECT_EQ(copyOfCopy[1], 9);
    EXPECT_EQ(copyOfCopy[2], 7);
    EXPECT_EQ(copyOfCopy[3944], -10);
    EXPECT_EQ(copyOfCopy[10000], 100);
    EXPECT_EQ(copyOfCopy[99], 99);
}

TEST(FragmentedDynamicArray, MoveConstructor) {
    IT("should move other FragmentedDynamicArray");
    TestArray empty;
    TestArray array = std::move(empty);
    EXPECT_TRUE(array.isEmpty());
    EXPECT_EQ(array.size(), 0);
    EXPECT_EQ(array.capacity(), 0);
    EXPECT_TRUE(array.isFull());
    array.addElement(2);
    array.addElement(9);
    array.addElement(7);
    EXPECT_FALSE(array.isEmpty());
    EXPECT_EQ(array.size(), 3);
    EXPECT_EQ(array.capacity(), 6);
    EXPECT_FALSE(array.isFull());
    TestArray moved = std::move(array);
    EXPECT_FALSE(moved.isEmpty());
    EXPECT_EQ(moved.size(), 3);
    EXPECT_EQ(moved.capacity(), 6);
    EXPECT_FALSE(moved.isFull());
    EXPECT_EQ(moved[0], 2);
    EXPECT_EQ(moved[1], 9);
    EXPECT_EQ(moved[2], 7);
    moved.addElement(-10, 3944);
    moved.addElement(100, 10000);
    EXPECT_FALSE(moved.isEmpty());
    EXPECT_EQ(moved.size(), 5);
    EXPECT_EQ(moved.capacity(), 8);
    EXPECT_FALSE(moved.isFull());
    moved.addElement(99, 99);
    EXPECT_EQ(moved.size(), 6);
    EXPECT_EQ(moved.capacity(), 12);
    EXPECT_FALSE(moved.isFull());
    TestArray doubleMoved = std::move(moved);
    EXPECT_EQ(doubleMoved.size(), 6);
    EXPECT_EQ(doubleMoved.capacity(), 12);
    EXPECT_FALSE(doubleMoved.isFull());
    EXPECT_EQ(doubleMoved[0], 2);
    EXPECT_EQ(doubleMoved[1], 9);
    EXPECT_EQ(doubleMoved[2], 7);
    EXPECT_EQ(doubleMoved[3944], -10);
    EXPECT_EQ(doubleMoved[10000], 100);
    EXPECT_EQ(doubleMoved[99], 99);
}

TEST(FragmentedDynamicArray, AssignOperator) {
    IT("copies into *this other FragmentedDynamicArray elements and sets capacity and size of the copy equal to other's size");
    TestArray empty;
    TestArray copyOfCopy;
    TestArray copy;
    TestArray array = empty;
    EXPECT_TRUE(array.isEmpty());
    EXPECT_EQ(array.size(), 0);
    EXPECT_EQ(array.capacity(), 0);
    EXPECT_TRUE(array.isFull());
    array.addElement(2);
    array.addElement(9);
    array.addElement(7);
    EXPECT_FALSE(array.isEmpty());
    EXPECT_EQ(array.size(), 3);
    EXPECT_EQ(array.capacity(), 6);
    EXPECT_FALSE(array.isFull());
    copy = array;
    EXPECT_FALSE(copy.isEmpty());
    EXPECT_EQ(copy.size(), 3);
    EXPECT_EQ(copy.capacity(), 3);
    EXPECT_TRUE(copy.isFull());
    EXPECT_EQ(copy[0], 2);
    EXPECT_EQ(copy[1], 9);
    EXPECT_EQ(copy[2], 7);
    copy.addElement(-10, 3944);
    copy.addElement(100, 10000);
    EXPECT_FALSE(array.isEmpty());
    EXPECT_EQ(array.size(), 3);
    EXPECT_EQ(array.capacity(), 6);
    EXPECT_FALSE(array.isFull());
    EXPECT_FALSE(copy.isEmpty());
    EXPECT_EQ(copy.size(), 5);
    EXPECT_EQ(copy.capacity(), 5);
    EXPECT_TRUE(copy.isFull());
    copy.addElement(99, 99);
    EXPECT_EQ(copy.size(), 6);
    EXPECT_EQ(copy.capacity(), 9);
    EXPECT_FALSE(copy.isFull());
    copyOfCopy = copy;
    EXPECT_EQ(copyOfCopy.size(), 6);
    EXPECT_EQ(copyOfCopy.capacity(), 6);
    EXPECT_TRUE(copyOfCopy.isFull());
    EXPECT_EQ(copyOfCopy[0], 2);
    EXPECT_EQ(copyOfCopy[1], 9);
    EXPECT_EQ(copyOfCopy[2], 7);
    EXPECT_EQ(copyOfCopy[3944], -10);
    EXPECT_EQ(copyOfCopy[10000], 100);
    EXPECT_EQ(copyOfCopy[99], 99);
}

TEST(FragmentedDynamicArray, MoveAssignOperator) {
    IT("move assign *this to other FragmentedDynamicArray");
    TestArray empty;
    TestArray moved;
    TestArray doubleMoved;
    TestArray array = std::move(empty);
    EXPECT_TRUE(array.isEmpty());
    EXPECT_EQ(array.size(), 0);
    EXPECT_EQ(array.capacity(), 0);
    EXPECT_TRUE(array.isFull());
    array.addElement(2);
    array.addElement(9);
    array.addElement(7);
    EXPECT_FALSE(array.isEmpty());
    EXPECT_EQ(array.size(), 3);
    EXPECT_EQ(array.capacity(), 6);
    EXPECT_FALSE(array.isFull());
    moved = std::move(array);
    EXPECT_FALSE(moved.isEmpty());
    EXPECT_EQ(moved.size(), 3);
    EXPECT_EQ(moved.capacity(), 6);
    EXPECT_FALSE(moved.isFull());
    EXPECT_EQ(moved[0], 2);
    EXPECT_EQ(moved[1], 9);
    EXPECT_EQ(moved[2], 7);
    moved.addElement(-10, 3944);
    moved.addElement(100, 10000);
    EXPECT_FALSE(moved.isEmpty());
    EXPECT_EQ(moved.size(), 5);
    EXPECT_EQ(moved.capacity(), 8);
    EXPECT_FALSE(moved.isFull());
    moved.addElement(99, 99);
    EXPECT_EQ(moved.size(), 6);
    EXPECT_EQ(moved.capacity(), 12);
    EXPECT_FALSE(moved.isFull());
    doubleMoved = std::move(moved);
    EXPECT_EQ(doubleMoved.size(), 6);
    EXPECT_EQ(doubleMoved.capacity(), 12);
    EXPECT_FALSE(doubleMoved.isFull());
    EXPECT_EQ(doubleMoved[0], 2);
    EXPECT_EQ(doubleMoved[1], 9);
    EXPECT_EQ(doubleMoved[2], 7);
    EXPECT_EQ(doubleMoved[3944], -10);
    EXPECT_EQ(doubleMoved[10000], 100);
    EXPECT_EQ(doubleMoved[99], 99);
}