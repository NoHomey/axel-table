#include "IndexedDynamicArray.htd"
#include "gtest/gtest.h"
#include "../../It/It.h"

using TestArray = IndexedDynamicArray<int>;

TEST(IndexedDynamicArray, addElement) {
    IT("adds new element and sort all elements");
    TestArray array;
    EXPECT_TRUE(array.isEmpty());
    EXPECT_EQ(array.size(), 0);
    EXPECT_EQ(array.capacity(), 0);
    EXPECT_TRUE(array.isFull());
    array.addElement(9, 18);
    EXPECT_FALSE(array.isEmpty());
    EXPECT_EQ(array.size(), 1);
    EXPECT_EQ(array.capacity(), 2);
    EXPECT_FALSE(array.isFull());
    array.addElement(19, 6);
    EXPECT_FALSE(array.isEmpty());
    EXPECT_EQ(array.size(), 2);
    EXPECT_EQ(array.capacity(), 2);
    EXPECT_TRUE(array.isFull());
    EXPECT_EQ(array[6], 19);
    EXPECT_EQ(array[18], 9);
    EXPECT_THROW(array[0],  ::IndexNotFound);
    EXPECT_THROW(array[1],  ::IndexNotFound);
    EXPECT_THROW(array[2],  ::IndexNotFound);
}

TEST(IndexedDynamicArray, indexOperator) {
    IT("checks if it can find element with the given index it it dose it returns it else throws exception");
    TestArray array;
    array.addElement(9, 18);
    EXPECT_EQ(array[18], 9);
    array.addElement(19, 6);
    EXPECT_EQ(array[6], 19);
    EXPECT_EQ(array[18], 9);
    EXPECT_THROW(array[0], ::IndexNotFound);
    EXPECT_THROW(array[1], ::IndexNotFound);
    EXPECT_THROW(array[2], ::IndexNotFound);
    array.addElement(33, 0);
    EXPECT_EQ(array[0], 33);
    EXPECT_THROW(array[1], ::IndexNotFound);
    array.addElement(42, 1);
    EXPECT_NO_THROW(array[1]);
    EXPECT_EQ(array[1], 42);
    EXPECT_THROW(array[2], ::IndexNotFound);
    array.clear();
    EXPECT_TRUE(array.isEmpty());
    EXPECT_THROW(array[1], ::EmptyDynamicArray);
}

TEST(IndexedDynamicArray, removeElement) {
    IT("removes the element at the given index if such index is found else it throw exception");
    TestArray array;
    EXPECT_TRUE(array.isEmpty());
    EXPECT_EQ(array.size(), 0);
    EXPECT_EQ(array.capacity(), 0);
    EXPECT_TRUE(array.isFull());
    EXPECT_THROW(array.removeElement(0), ::EmptyDynamicArray);
    array.addElement(19, 6);
    EXPECT_FALSE(array.isEmpty());
    EXPECT_EQ(array.size(), 1);
    EXPECT_EQ(array.capacity(), 2);
    EXPECT_FALSE(array.isFull());
    array.removeElement(6);
    EXPECT_TRUE(array.isEmpty());
    EXPECT_EQ(array.size(), 0);
    EXPECT_EQ(array.capacity(), 2);
    EXPECT_FALSE(array.isFull());
    array.addElement(7, 2);
    array.addElement(3, 3);
    EXPECT_THROW(array[0], ::IndexNotFound);
    EXPECT_THROW(array[1], ::IndexNotFound);
    array.removeElement(2);
    EXPECT_THROW(array.removeElement(2), ::IndexNotFound);
    array.removeElement(3);
    EXPECT_THROW(array.removeElement(3), ::EmptyDynamicArray);
}

TEST(IndexDynamicArray, SizeConstructor) {
    IT("should create empty IndexDynamicArray with capacity equal to provided size");
    TestArray array{9};
    EXPECT_TRUE(array.isEmpty());
    EXPECT_EQ(array.size(), 0);
    EXPECT_EQ(array.capacity(), 9);
    EXPECT_FALSE(array.isFull());
    EXPECT_THROW(array.removeElement(0), ::EmptyDynamicArray);
    TestArray empty{0};
    EXPECT_EQ(empty.size(), 0);
    EXPECT_EQ(empty.capacity(), 0);
    EXPECT_TRUE(empty.isFull());
    EXPECT_THROW(empty.removeElement(2), ::EmptyDynamicArray);
}