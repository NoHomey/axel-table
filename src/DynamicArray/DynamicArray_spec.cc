#include "DynamicArray.htd"
#include "gtest/gtest.h"
#include "../It/It.h"

using TestArray = DynamicArray<int>;

TEST(DynamicArray, DefaultConstructor) {
    IT("should create empty array with no capacity");
    TestArray array;
    EXPECT_TRUE(array.isEmpty());
    EXPECT_EQ(array.size(), 0);
    EXPECT_EQ(array.capacity(), 0);
    EXPECT_TRUE(array.isFull());
    EXPECT_THROW(array.pop(), ::EmptyDynamicArray);
}

TEST(DynamicArray, SizeConstructor) {
    IT("should create empty array with capacity equal to provided size");
    TestArray array{9};
    EXPECT_TRUE(array.isEmpty());
    EXPECT_EQ(array.size(), 0);
    EXPECT_EQ(array.capacity(), 9);
    EXPECT_FALSE(array.isFull());
    EXPECT_THROW(array.pop(), ::EmptyDynamicArray);
    array.push(9);
    EXPECT_FALSE(array.isEmpty());
    EXPECT_EQ(array.size(), 1);
    EXPECT_EQ(array.capacity(), 9);
    EXPECT_FALSE(array.isFull());
    EXPECT_NO_THROW(array.pop());
    for(size_t i = 0; i < 9; ++i) {
        array.push(i);
    }
    EXPECT_FALSE(array.isEmpty());
    EXPECT_EQ(array.size(), 9);
    EXPECT_EQ(array.capacity(), 9);
    EXPECT_TRUE(array.isFull());
    EXPECT_NO_THROW(array.pop());
    for(size_t i = 42; i < 47; ++i) {
        array.push(i);
    }
    EXPECT_FALSE(array.isEmpty());
    EXPECT_EQ(array.size(), 13);
    EXPECT_EQ(array.capacity(), 18);
    EXPECT_FALSE(array.isFull());
    EXPECT_NO_THROW(array.pop());
    array.shrinkToFit();
    EXPECT_FALSE(array.isEmpty());
    EXPECT_EQ(array.size(), 12);
    EXPECT_EQ(array.capacity(), 12);
    EXPECT_TRUE(array.isFull());
    EXPECT_NO_THROW(array.pop());
    array.clear();
    EXPECT_TRUE(array.isEmpty());
    EXPECT_EQ(array.size(), 0);
    EXPECT_EQ(array.capacity(), 0);
    EXPECT_TRUE(array.isFull());
    EXPECT_THROW(array.pop(), ::EmptyDynamicArray);
}