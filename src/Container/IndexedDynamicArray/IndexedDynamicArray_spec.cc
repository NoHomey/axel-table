#include "IndexedDynamicArray.htd"
#include "gtest/gtest.h"
#include "../../It/It.h"

using TestArray = IndexedDynamicArray<int>;

TEST(IndexedDynamicArray, DefaultConstructor) {
    IT("should create empty IndexedDynamicArray with no capacity");
    TestArray array;
    EXPECT_TRUE(array.isEmpty());
    EXPECT_EQ(array.size(), 0);
    EXPECT_EQ(array.capacity(), 0);
    EXPECT_TRUE(array.isFull());
}

TEST(IndexedDynamicArray, indexOperator) {
    IT("checks if it can find element with the given index it it dose it returns it else throws exception");
    TestArray array;
    array.setElement(9, 1800);
    EXPECT_EQ(array[1800], 9);
    array.setElement(19, 283);
    EXPECT_EQ(array[283], 19);
    EXPECT_EQ(array[1800], 9);
    EXPECT_THROW(array[0], ::IndexNotFound);
    EXPECT_THROW(array[1], ::IndexNotFound);
    EXPECT_THROW(array[2], ::IndexNotFound);
    array.setElement(33, 0);
    EXPECT_EQ(array[0], 33);
    EXPECT_THROW(array[1], ::IndexNotFound);
    array.setElement(42, 1);
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
    array.setElement(19, 6);
    EXPECT_FALSE(array.isEmpty());
    EXPECT_EQ(array.size(), 1);
    EXPECT_EQ(array.capacity(), 2);
    EXPECT_FALSE(array.isFull());
    array.removeElement(6);
    EXPECT_TRUE(array.isEmpty());
    EXPECT_EQ(array.size(), 0);
    EXPECT_EQ(array.capacity(), 2);
    EXPECT_FALSE(array.isFull());
    array.setElement(7, 2);
    array.setElement(3, 3);
    EXPECT_THROW(array[0], ::IndexNotFound);
    EXPECT_THROW(array[1], ::IndexNotFound);
    array.removeElement(2);
    EXPECT_THROW(array.removeElement(2), ::IndexNotFound);
    array.removeElement(3);
    EXPECT_THROW(array.removeElement(3), ::EmptyDynamicArray);
}

TEST(IndexedDynamicArray, SizeConstructor) {
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

TEST(IndexedDynamicArray, shrinkToFit) {
    IT("if not full allocates new IndexedDynamicArray with capacity equal to size the copy all elements, dealocates old memory and moves assigns it");
    TestArray array;
    EXPECT_EQ(array.capacity(), 0);
    array.setElement(9, 9);
    EXPECT_EQ(array.capacity(), 2);
    EXPECT_EQ(array.size(), 1);
    array.shrinkToFit();
    EXPECT_EQ(array.size(), 1);
    EXPECT_EQ(array.capacity(), 1);
    array.setElement(4, 44);
    array.setElement(2, 32);
    array.setElement(1, 111);
    EXPECT_EQ(array.capacity(), 4);
    EXPECT_EQ(array.size(), 4);
    array.shrinkToFit();
    EXPECT_EQ(array.size(), 4);
    EXPECT_EQ(array.capacity(), 4);
    for(size_t i = 0; i < 9; ++i) {
        array.setElement(i, 10 * i * i + i);
    }
    EXPECT_EQ(array.capacity(), 22);
    EXPECT_EQ(array.size(), 13);
    array.shrinkToFit();
    EXPECT_EQ(array.size(), 13);
    EXPECT_EQ(array.capacity(), 13);
}

TEST(IndexedDynamicArray, clear) {
    IT("clears IndexedDynamicArray content and resets size and capacity");
    TestArray array;
    EXPECT_TRUE(array.isEmpty());
    array.setElement(9, 11);
    EXPECT_EQ(array.capacity(), 2);
    EXPECT_EQ(array.size(), 1);
    EXPECT_FALSE(array.isEmpty());
    EXPECT_FALSE(array.isFull());
    array.clear();
    EXPECT_TRUE(array.isEmpty());
    EXPECT_EQ(array.size(), 0);
    EXPECT_EQ(array.capacity(), 0);
    EXPECT_TRUE(array.isFull());
    array.setElement(4, 33);
    array.setElement(2, 2);
    array.setElement(1, 29);
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
        array.setElement(i, 1000 * i);
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

TEST(IndexedDynamicArray, reserve) {
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

TEST(IndexedDynamicArray, getElement) {
    IT("returns element at given index, checks for emptiness and invalid index");
    TestArray array;
    EXPECT_THROW(array.getElement(0), ::EmptyDynamicArray);
    array.setElement(9,7);
    EXPECT_THROW(array.getElement(0), ::IndexNotFound);
    EXPECT_EQ(array.getElement(7), 9);
    EXPECT_THROW(array.getElement(1), ::IndexNotFound);
    EXPECT_THROW(array.getElement(9), ::IndexNotFound);
    EXPECT_THROW(array.getElement(2), ::IndexNotFound);
    array.clear();
    EXPECT_THROW(array.getElement(0), ::EmptyDynamicArray);
    array.setElement(9,7623);
    EXPECT_EQ(array.getElement(7623), 9);
    EXPECT_THROW(array.getElement(7621), ::IndexNotFound);
    EXPECT_THROW(array.getElement(7622), ::IndexNotFound);
    EXPECT_THROW(array.getElement(7624), ::IndexNotFound);
}

TEST(IndexedDynamicArray, setElement) {
    IT("sets element at given index if index is greater than DynamicArray size's throws exception");
    TestArray array;
    array.setElement(2, 2);
    EXPECT_NO_THROW(array.getElement(2));
    EXPECT_EQ(array.getElement(2), 2);
    array.setElement(5, 4);
    array.setElement(1, 6);
    EXPECT_NO_THROW(array.getElement(4));
    EXPECT_NO_THROW(array.getElement(6));
    EXPECT_EQ(array.getElement(6), 1);
    array.setElement(9, 6);
    EXPECT_EQ(array.getElement(6), 9);
    EXPECT_EQ(array.getElement(4), 5);
    array.setElement(2, 4);
    EXPECT_EQ(array.getElement(4), 2);
}

TEST(IndexedDynamicArray, isEmpty) {
    IT("returns true if IndexedDynamicArray's size is equal to 0");
    TestArray array;
    EXPECT_TRUE(array.isEmpty());
    array.setElement(9, 100);
    EXPECT_FALSE(array.isEmpty());
}

TEST(IndexedDynamicArray, isFull) {
    IT("returns true if IndexedDynamicArray's size is equal to it's capacity");
    TestArray array;
    EXPECT_TRUE(array.isFull());
    array.setElement(9, 100);
    EXPECT_FALSE(array.isFull());
    EXPECT_EQ(array.size(), 1);
    EXPECT_EQ(array.capacity(), 2);
    array.setElement(3, 3);
    EXPECT_TRUE(array.isFull());
    EXPECT_EQ(array.size(), 2);
    EXPECT_EQ(array.capacity(), 2);
    array.setElement(-100, 9999);
    EXPECT_FALSE(array.isFull());
    EXPECT_EQ(array.size(), 3);
    EXPECT_EQ(array.capacity(), 6);
}

TEST(IndexedDynamicArray, size) {
    IT("returns the count of elements in the IndxedDynamicArray");
    TestArray array;
    EXPECT_EQ(array.size(), 0);
    array.setElement(9, 3);
    EXPECT_EQ(array.size(), 1);
    array.setElement(4, 100);
    array.setElement(22, 231);
    EXPECT_EQ(array.size(), 3);
    for(size_t i = 0; i < 11; ++i) {
        array.setElement(i, 2 * i);
    }
    EXPECT_EQ(array.size(), 14);
}

TEST(IndexedDynamicArray, capacity) {
    IT("returns the size of dynamically allocated memory for the IndexedDynamicArray's elements");
    TestArray array;
    EXPECT_EQ(array.size(), 0);
    array.setElement(9, 3);
    EXPECT_EQ(array.capacity(), 2);
    array.setElement(4, 100);
    array.setElement(22, 231);
    EXPECT_EQ(array.capacity(), 6);
    for(size_t i = 0; i < 11; ++i) {
        array.setElement(i, 2 * i);
    }
    EXPECT_EQ(array.size(), 14);
    EXPECT_EQ(array.capacity(), 14);
    EXPECT_TRUE(array.isFull());
    array.setElement(-342, 43583);
    EXPECT_EQ(array.size(), 15);
    EXPECT_EQ(array.capacity(), 30);
    EXPECT_FALSE(array.isFull());
}

TEST(IndexedDynamicArray, CopyConstructor) {
    IT("should copy other IndexedDynamicArray and sets capacity and size of the copy equal to other's size");
    TestArray empty;
    TestArray array = empty;
    EXPECT_TRUE(array.isEmpty());
    EXPECT_EQ(array.size(), 0);
    EXPECT_EQ(array.capacity(), 0);
    EXPECT_TRUE(array.isFull());
    array.setElement(-222, 222);
    array.setElement(9, 13);
    array.setElement(7, 96);
    EXPECT_FALSE(array.isEmpty());
    EXPECT_EQ(array.size(), 3);
    EXPECT_EQ(array.capacity(), 6);
    EXPECT_FALSE(array.isFull());
    TestArray copy = array;
    EXPECT_FALSE(copy.isEmpty());
    EXPECT_EQ(copy.size(), 3);
    EXPECT_EQ(copy.capacity(), 3);
    EXPECT_TRUE(copy.isFull());
    EXPECT_EQ(copy[222], -222);
    EXPECT_EQ(copy[13], 9);
    EXPECT_EQ(copy[96], 7);
    copy.setElement(-111, 19348);
    EXPECT_FALSE(copy.isEmpty());
    EXPECT_EQ(copy.size(), 4);
    EXPECT_EQ(copy.capacity(), 8);
    EXPECT_FALSE(copy.isFull());
}

TEST(IndexedDynamicArray, MoveConstructor) {
    IT("should move other IndexedDynamicArray");
    TestArray empty;
    TestArray array = std::move(empty);
    EXPECT_TRUE(array.isEmpty());
    EXPECT_EQ(array.size(), 0);
    EXPECT_EQ(array.capacity(), 0);
    EXPECT_TRUE(array.isFull());
    array.setElement(-222, 222);
    array.setElement(9, 13);
    array.setElement(7, 96);
    EXPECT_FALSE(array.isEmpty());
    EXPECT_EQ(array.size(), 3);
    EXPECT_EQ(array.capacity(), 6);
    EXPECT_FALSE(array.isFull());
    TestArray moved = std::move(array);
    EXPECT_FALSE(moved.isEmpty());
    EXPECT_EQ(moved.size(), 3);
    EXPECT_EQ(moved.capacity(), 6);
    EXPECT_FALSE(moved.isFull());
    EXPECT_EQ(moved[222], -222);
    EXPECT_EQ(moved[13], 9);
    EXPECT_EQ(moved[96], 7);
}

TEST(IndexedDynamicArray, AssignOperator) {
    IT("copies into *this other IndexedDynamicArray elements and sets capacity and size of the copy equal to other's size");
    TestArray empty;
    TestArray copy;
    TestArray array = empty;
    EXPECT_TRUE(array.isEmpty());
    EXPECT_EQ(array.size(), 0);
    EXPECT_EQ(array.capacity(), 0);
    EXPECT_TRUE(array.isFull());
    array.setElement(-222, 222);
    array.setElement(9, 13);
    array.setElement(7, 96);
    EXPECT_FALSE(array.isEmpty());
    EXPECT_EQ(array.size(), 3);
    EXPECT_EQ(array.capacity(), 6);
    EXPECT_FALSE(array.isFull());
    copy = array;
    EXPECT_FALSE(copy.isEmpty());
    EXPECT_EQ(copy.size(), 3);
    EXPECT_EQ(copy.capacity(), 3);
    EXPECT_TRUE(copy.isFull());
    EXPECT_EQ(copy[222], -222);
    EXPECT_EQ(copy[13], 9);
    EXPECT_EQ(copy[96], 7);
    copy.setElement(-111, 19348);
    EXPECT_FALSE(copy.isEmpty());
    EXPECT_EQ(copy.size(), 4);
    EXPECT_EQ(copy.capacity(), 8);
    EXPECT_FALSE(copy.isFull());
}

TEST(IndexedDynamicArray, MoveAssignOperator) {
    IT("move assign *this to other IndexedDynamicArray");
    TestArray empty;
    TestArray moved;
    TestArray array = std::move(empty);
    EXPECT_TRUE(array.isEmpty());
    EXPECT_EQ(array.size(), 0);
    EXPECT_EQ(array.capacity(), 0);
    EXPECT_TRUE(array.isFull());
    array.setElement(-222, 222);
    array.setElement(9, 13);
    array.setElement(7, 96);
    EXPECT_FALSE(array.isEmpty());
    EXPECT_EQ(array.size(), 3);
    EXPECT_EQ(array.capacity(), 6);
    EXPECT_FALSE(array.isFull());
    moved = std::move(array);
    EXPECT_FALSE(moved.isEmpty());
    EXPECT_EQ(moved.size(), 3);
    EXPECT_EQ(moved.capacity(), 6);
    EXPECT_FALSE(moved.isFull());
    EXPECT_EQ(moved[222], -222);
    EXPECT_EQ(moved[13], 9);
    EXPECT_EQ(moved[96], 7);
}

TEST(IndexedDynamicArray, forEach) {
    IT("makes a function like call to the given function-like passing element and it's index for each element");

    class Expecter {
    public:
        Expecter(): position{0} { }

        void operator()(int element, size_t index) {
            EXPECT_EQ(element, data[position]);
            EXPECT_EQ(index, indexes[position]);
            ++position;
        }
    private:
        size_t position;
        const int data[10] = {3, 6, 123, 22, 1, 9549, 5, 6, -343, 971};
        const size_t indexes[10] = {2, 13, 17, 42, 45, 53, 81, 454, 678, 9999};
    };

    TestArray array{10};
    array.setElement(1, 45);
    array.setElement(6, 454);
    array.setElement(3, 2);
    array.setElement(6, 13);
    array.setElement(22, 42);
    array.setElement(9549, 53);
    array.setElement(-343, 678);
    array.setElement(123, 17);
    array.setElement(5, 81);
    array.setElement(971, 9999);

    Expecter expecter;
    array.forEach(expecter);
}