#include "DynamicArray.htd"
#include "gtest/gtest.h"
#include "../../It/It.h"

using TestArray = DynamicArray<int>;

TEST(DynamicArray, DefaultConstructor) {
    IT("should create empty DynamicArray with no capacity");
    TestArray array;
    EXPECT_TRUE(array.isEmpty());
    EXPECT_EQ(array.size(), 0);
    EXPECT_EQ(array.capacity(), 0);
    EXPECT_TRUE(array.isFull());
    EXPECT_THROW(array.pop(), ::EmptyDynamicArray);
}

TEST(DynamicArray, SizeConstructor) {
    IT("should create empty DynamicArray with capacity equal to provided size");
    TestArray array{9};
    EXPECT_TRUE(array.isEmpty());
    EXPECT_EQ(array.size(), 0);
    EXPECT_EQ(array.capacity(), 9);
    EXPECT_FALSE(array.isFull());
    EXPECT_THROW(array.pop(), ::EmptyDynamicArray);
    TestArray empty{0};
    EXPECT_TRUE(empty.isEmpty());
    EXPECT_EQ(empty.size(), 0);
    EXPECT_EQ(empty.capacity(), 0);
    EXPECT_TRUE(empty.isFull());
    EXPECT_THROW(empty.pop(), ::EmptyDynamicArray);
}

TEST(DynamicArray, isEmpty) {
    IT("returns true if DynamicArray's size is equal to 0");
    TestArray array;
    EXPECT_TRUE(array.isEmpty());
    array.push(9);
    EXPECT_FALSE(array.isEmpty());
}

TEST(DynamicArray, isFull) {
    IT("returns true if DynamicArray's size is equal to it's capacity");
    TestArray array;
    EXPECT_TRUE(array.isFull());
    array.push(9);
    EXPECT_FALSE(array.isFull());
    EXPECT_EQ(array.size(), 1);
    EXPECT_EQ(array.capacity(), 2);
    array.push(3);
    EXPECT_TRUE(array.isFull());
    EXPECT_EQ(array.size(), 2);
    EXPECT_EQ(array.capacity(), 2);
}

TEST(DynamicArray, size) {
    IT("returns the count of elements in the DynamicArray");
    TestArray array;
    EXPECT_EQ(array.size(), 0);
    array.push(9);
    EXPECT_EQ(array.size(), 1);
    array.pop();
    EXPECT_EQ(array.size(), 0);
    array.push(4);
    array.push(2);
    EXPECT_EQ(array.size(), 2);
    array.pop();
    for(size_t i = 0; i < 9; ++i) {
        array.push(i);
    }
    EXPECT_EQ(array.size(), 10);
    array.pop();
    EXPECT_EQ(array.size(), 9);
}

TEST(DynamicArray, capacity) {
    IT("returns the size of dynamically allocated memory for the DynamicArray's elements");
    TestArray array;
    EXPECT_EQ(array.capacity(), 0);
    array.push(9);
    EXPECT_EQ(array.capacity(), 2);
    array.pop();
    EXPECT_EQ(array.capacity(), 2);
    array.push(4);
    array.push(2);
    array.push(1);
    EXPECT_EQ(array.capacity(), 6);
    array.pop();
    for(size_t i = 0; i < 9; ++i) {
        array.push(i);
    }
    EXPECT_EQ(array.capacity(), 14);
    array.pop();
    EXPECT_EQ(array.capacity(), 14);
}

TEST(DynamicArray, push) {
    IT("adds new element to the DynamicArray if it is full it will also resize it to capacity equal to [2 x size]");
    TestArray array;
    array.push(9);
    EXPECT_FALSE(array.isEmpty());
    EXPECT_EQ(array.size(), 1);
    EXPECT_EQ(array.capacity(), 2);
    EXPECT_FALSE(array.isFull());
    EXPECT_NO_THROW(array.pop());
    for(size_t i = 0; i < 9; ++i) {
        array.push(i);
    }
    EXPECT_FALSE(array.isEmpty());
    EXPECT_EQ(array.size(), 9);
    EXPECT_EQ(array.capacity(), 14);
    EXPECT_FALSE(array.isFull());
    EXPECT_NO_THROW(array.pop());
    for(size_t i = 42; i < 47; ++i) {
        array.push(i);
    }
    EXPECT_FALSE(array.isEmpty());
    EXPECT_EQ(array.size(), 13);
    EXPECT_EQ(array.capacity(), 14);
    EXPECT_FALSE(array.isFull());
    array.push(22);
    EXPECT_EQ(array.size(), 14);
    EXPECT_EQ(array.capacity(), 14);
    EXPECT_TRUE(array.isFull());
    array.push(23);
    EXPECT_EQ(array.size(), 15);
    EXPECT_EQ(array.capacity(), 30);
    EXPECT_FALSE(array.isFull());
    EXPECT_NO_THROW(array.pop());
}

TEST(DynamicArray, shrinkToFit) {
    IT("if not full allocates new DynamicArray with capacity equal to size the copy all elements, dealocates old memory and moves assigns it");
    TestArray array;
    EXPECT_EQ(array.capacity(), 0);
    array.push(9);
    EXPECT_EQ(array.capacity(), 2);
    EXPECT_EQ(array.size(), 1);
    array.shrinkToFit();
    EXPECT_EQ(array.size(), 1);
    EXPECT_EQ(array.capacity(), 1);
    array.push(4);
    array.push(2);
    array.push(1);
    EXPECT_EQ(array.capacity(), 4);
    EXPECT_EQ(array.size(), 4);
    array.shrinkToFit();
    EXPECT_EQ(array.size(), 4);
    EXPECT_EQ(array.capacity(), 4);
    for(size_t i = 0; i < 9; ++i) {
        array.push(i);
    }
     EXPECT_EQ(array.capacity(), 22);
    EXPECT_EQ(array.size(), 13);
    array.shrinkToFit();
    EXPECT_EQ(array.size(), 13);
    EXPECT_EQ(array.capacity(), 13);
}

TEST(DynamicArray, clear) {
    IT("clears DynamicArray content and resets size and capacity");
    TestArray array;
    EXPECT_TRUE(array.isEmpty());
    array.push(9);
    EXPECT_EQ(array.capacity(), 2);
    EXPECT_EQ(array.size(), 1);
    EXPECT_FALSE(array.isEmpty());
    EXPECT_FALSE(array.isFull());
    array.clear();
    EXPECT_TRUE(array.isEmpty());
    EXPECT_EQ(array.size(), 0);
    EXPECT_EQ(array.capacity(), 0);
    EXPECT_TRUE(array.isFull());
    array.push(4);
    array.push(2);
    array.push(1);
    EXPECT_EQ(array.capacity(), 6);
    EXPECT_EQ(array.size(), 3);
    EXPECT_FALSE(array.isEmpty());
    EXPECT_FALSE(array.isFull());
    array.clear();
    EXPECT_TRUE(array.isEmpty());
    EXPECT_EQ(array.size(), 0);
    EXPECT_EQ(array.capacity(), 0);
    EXPECT_TRUE(array.isFull());
    for(size_t i = 0; i < 9; ++i) {
        array.push(i);
    }
    EXPECT_EQ(array.capacity(), 14);
    EXPECT_EQ(array.size(), 9);
    EXPECT_FALSE(array.isEmpty());
    EXPECT_FALSE(array.isFull());
    array.clear();
    EXPECT_TRUE(array.isEmpty());
    EXPECT_EQ(array.size(), 0);
    EXPECT_EQ(array.capacity(), 0);
    EXPECT_TRUE(array.isFull());
}

TEST(DynamicArray, reserve) {
    IT("reserves capacity for elements by making a reallocation");
    TestArray array;
    EXPECT_EQ(array.capacity(), 0);
    array.reserve(7);
    EXPECT_EQ(array.capacity(), 7);
    array.reserve(0);
    EXPECT_EQ(array.capacity(), 7);
    array.clear();
    EXPECT_EQ(array.capacity(), 0);
    array.reserve(6);
    EXPECT_EQ(array.capacity(), 6);
}

TEST(DynamicArray, indexOperator) {
    IT("returns element at the given index without making any checks");
    TestArray array;
    for(size_t i = 0; i < 9; ++i) {
        array.push(i);
    }
    for(size_t i = 0; i < 9; ++i) {
        EXPECT_EQ(array[i], i);
    }
}

TEST(DynamicArray, CopyConstructor) {
    IT("should copy other DynamicArray and sets capacity and size of the copy equal to other's size");
    TestArray empty;
    TestArray array = empty;
    EXPECT_TRUE(array.isEmpty());
    EXPECT_EQ(array.size(), 0);
    EXPECT_EQ(array.capacity(), 0);
    EXPECT_TRUE(array.isFull());
    array.push(2);
    array.push(9);
    array.push(7);
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
    copy.push(213);
    EXPECT_FALSE(array.isEmpty());
    EXPECT_EQ(array.size(), 3);
    EXPECT_EQ(array.capacity(), 6);
    EXPECT_FALSE(array.isFull());
    EXPECT_FALSE(copy.isEmpty());
    EXPECT_EQ(copy.size(), 4);
    EXPECT_EQ(copy.capacity(), 8);
    EXPECT_FALSE(copy.isFull());
}

TEST(DynamicArray, MoveConstructor) {
    IT("should move other DynamicArray");
    TestArray empty;
    TestArray array = std::move(empty);
    EXPECT_TRUE(array.isEmpty());
    EXPECT_EQ(array.size(), 0);
    EXPECT_EQ(array.capacity(), 0);
    EXPECT_TRUE(array.isFull());
    array.push(2);
    array.push(9);
    array.push(7);
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
    EXPECT_TRUE(array.isEmpty());
    EXPECT_EQ(array.size(), 0);
    EXPECT_EQ(array.capacity(), 0);
    EXPECT_TRUE(array.isFull());
}

TEST(DynamicArray, AssignOperator) {
    IT("copies into *this other DynamicArray elements and sets capacity and size of the copy equal to other's size");
    TestArray empty;
    TestArray array;
    TestArray tmp;
    array.push(2);
    array.push(9);
    array.push(7);
    EXPECT_FALSE(array.isEmpty());
    EXPECT_EQ(array.size(), 3);
    EXPECT_EQ(array.capacity(), 6);
    EXPECT_FALSE(array.isFull());
    tmp = array;
    array = empty;
    EXPECT_TRUE(array.isEmpty());
    EXPECT_EQ(array.size(), 0);
    EXPECT_EQ(array.capacity(), 0);
    EXPECT_TRUE(array.isFull());
    EXPECT_FALSE(tmp.isEmpty());
    EXPECT_EQ(tmp.size(), 3);
    EXPECT_EQ(tmp.capacity(), 3);
    EXPECT_TRUE(tmp.isFull());
    EXPECT_EQ(tmp[0], 2);
    EXPECT_EQ(tmp[1], 9);
    EXPECT_EQ(tmp[2], 7);
    tmp = tmp;
    EXPECT_FALSE(tmp.isEmpty());
    EXPECT_EQ(tmp.size(), 3);
    EXPECT_EQ(tmp.capacity(), 3);
    EXPECT_TRUE(tmp.isFull());
    EXPECT_EQ(tmp[0], 2);
    EXPECT_EQ(tmp[1], 9);
    EXPECT_EQ(tmp[2], 7);
    tmp.push(213);
    EXPECT_TRUE(array.isEmpty());
    EXPECT_EQ(array.size(), 0);
    EXPECT_EQ(array.capacity(), 0);
    EXPECT_TRUE(array.isFull());
    EXPECT_FALSE(tmp.isEmpty());
    EXPECT_EQ(tmp.size(), 4);
    EXPECT_EQ(tmp.capacity(), 8);
    EXPECT_FALSE(tmp.isFull());
}

TEST(DynamicArray, MoveAssignOperator) {
    IT("move assign *this to other DynamicArray");
    TestArray empty;
    TestArray array;
    TestArray tmp;
    array.push(2);
    array.push(9);
    array.push(7);
    EXPECT_FALSE(array.isEmpty());
    EXPECT_EQ(array.size(), 3);
    EXPECT_EQ(array.capacity(), 6);
    EXPECT_FALSE(array.isFull());
    tmp = std::move(array);
    EXPECT_TRUE(array.isEmpty());
    EXPECT_EQ(array.size(), 0);
    EXPECT_EQ(array.capacity(), 0);
    EXPECT_TRUE(array.isFull());
    EXPECT_FALSE(tmp.isEmpty());
    EXPECT_EQ(tmp.size(), 3);
    EXPECT_EQ(tmp.capacity(), 6);
    EXPECT_FALSE(tmp.isFull());
    EXPECT_EQ(tmp[0], 2);
    EXPECT_EQ(tmp[1], 9);
    EXPECT_EQ(tmp[2], 7);
    tmp = std::move(tmp);
    EXPECT_FALSE(tmp.isEmpty());
    EXPECT_EQ(tmp.size(), 3);
    EXPECT_EQ(tmp.capacity(), 6);
    EXPECT_FALSE(tmp.isFull());
    EXPECT_EQ(tmp[0], 2);
    EXPECT_EQ(tmp[1], 9);
    EXPECT_EQ(tmp[2], 7);
    EXPECT_TRUE(empty.isEmpty());
    EXPECT_EQ(empty.size(), 0);
    EXPECT_EQ(empty.capacity(), 0);
    EXPECT_TRUE(empty.isFull());
    tmp = std::move(empty);
    EXPECT_TRUE(tmp.isEmpty());
    EXPECT_EQ(tmp.size(), 0);
    EXPECT_EQ(tmp.capacity(), 0);
    EXPECT_TRUE(tmp.isFull());
}

TEST(DynamicArray, getElement) {
    IT("returns element at given index, checks for emptiness and invalid index");
    TestArray array;
    EXPECT_THROW(array.getElement(0), ::EmptyDynamicArray);
    EXPECT_THROW(array.getElement(100), ::EmptyDynamicArray);
    array.push(9);
    EXPECT_NO_THROW(array.getElement(0));
    EXPECT_EQ(array.getElement(0), 9);
    EXPECT_THROW(array.getElement(1), ::IndexNotFound);
    EXPECT_THROW(array.getElement(2), ::IndexNotFound);
    array.push(7);
    EXPECT_NO_THROW(array.getElement(1));
    EXPECT_EQ(array.getElement(1), 7);
    EXPECT_THROW(array.getElement(2), ::IndexNotFound);
    array.clear();
    EXPECT_THROW(array.getElement(0), ::EmptyDynamicArray);
}

TEST(DynamicArray, setElement) {
    IT("sets element at given index if index is greater than DynamicArray size's throws exception");
    TestArray array;
    EXPECT_THROW(array.setElement(2, 1), ::IndexNotFound);
    array.setElement(2, 0);
    EXPECT_NO_THROW(array.getElement(0));
    EXPECT_EQ(array.getElement(0), 2);
    EXPECT_THROW(array.setElement(1, 2), ::IndexNotFound);
    EXPECT_THROW(array.setElement(1, 3), ::IndexNotFound);
    array.setElement(9, 1);
    EXPECT_NO_THROW(array.getElement(1));
    EXPECT_EQ(array.getElement(1), 9);
    EXPECT_THROW(array.getElement(2), ::IndexNotFound);
    array.setElement(9, 2);
    EXPECT_NO_THROW(array.getElement(2));
    EXPECT_EQ(array.getElement(2), 9);
    array.setElement(2, 2);
    EXPECT_EQ(array.getElement(2), 2);
    array.setElement(5, 2);
    EXPECT_EQ(array.getElement(2), 5);
}

TEST(DynamicArray, forEach) {
    IT("makes a function like call to the given function-like passing element and it's index for each element");

    TestArray array{10};
    array.push(1);
    array.push(6);
    array.push(3);
    array.push(6);
    array.push(22);
    array.push(9549);
    array.push(-343);
    array.push(123);
    array.push(5);
    array.push(971);

    const int data[10] = {1, 6, 3, 6, 22, 9549, -343, 123, 5, 971};
    const size_t indexes[10] = {0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    size_t position = 0;

    array.forEach([&data, &indexes, &position](int element, size_t index) {
        EXPECT_EQ(element, data[position]);
        EXPECT_EQ(index, indexes[position]);
        ++position;
    });
    EXPECT_EQ(position, 10);
}