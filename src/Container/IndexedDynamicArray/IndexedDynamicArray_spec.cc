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

TEST(DynamicArray, hasElementAt) {
    IT("returns true if there is element at the given index");
    TestArray array;
    array.setElement(1800, 9);
    EXPECT_TRUE(array.hasElementAt(1800));
    array.setElement(283, 19);
    EXPECT_TRUE(array.hasElementAt(283));
    EXPECT_TRUE(array.hasElementAt(1800));
    EXPECT_FALSE(array.hasElementAt(0));
    EXPECT_FALSE(array.hasElementAt(1));
    EXPECT_FALSE(array.hasElementAt(2));
    array.setElement(0, 33);
    EXPECT_TRUE(array.hasElementAt(0));
    EXPECT_FALSE(array.hasElementAt(1));
    array.setElement(1, 42);
    EXPECT_TRUE(array.hasElementAt(1));
    EXPECT_FALSE(array.hasElementAt(2));
    array.clear();
    EXPECT_TRUE(array.isEmpty());
    EXPECT_FALSE(array.hasElementAt(0));
    for(int i = 0; i < 30; ++i) {
        array.setElement(i * i + i, i * i);
        EXPECT_TRUE(array.hasElementAt(i * i + i));
    }
}

TEST(IndexedDynamicArray, indexOperator) {
    IT("returns element at the given index");
    TestArray array;
    array.setElement(1800, 9);
    EXPECT_TRUE(array.hasElementAt(1800));
    array.setElement(283, 19);
    EXPECT_EQ(array[283], 19);
    EXPECT_EQ(array[1800], 9);
    array.setElement(0, 33);
    EXPECT_EQ(array[0], 33);
    array.setElement(1, 42);
    EXPECT_EQ(array[1], 42);
    array.clear();
    EXPECT_TRUE(array.isEmpty());
}

TEST(IndexedDynamicArray, removeElement) {
    IT("removes the element at the given index if such index is found else it throw exception");
    TestArray array;
    EXPECT_TRUE(array.isEmpty());
    EXPECT_EQ(array.size(), 0);
    EXPECT_EQ(array.capacity(), 0);
    EXPECT_TRUE(array.isFull());
    array.setElement(6, 19);
    EXPECT_FALSE(array.isEmpty());
    EXPECT_EQ(array.size(), 1);
    EXPECT_EQ(array.capacity(), 2);
    EXPECT_FALSE(array.isFull());
    array.removeElement(6);
    EXPECT_TRUE(array.isEmpty());
    EXPECT_EQ(array.size(), 0);
    EXPECT_EQ(array.capacity(), 2);
    EXPECT_FALSE(array.isFull());
    array.setElement(2, 7);
    array.setElement(3, 3);
    EXPECT_FALSE(array.hasElementAt(0));
    EXPECT_FALSE(array.hasElementAt(1));
    array.removeElement(2);
    EXPECT_FALSE(array.hasElementAt(2));
    array.removeElement(3);
    EXPECT_FALSE(array.hasElementAt(3));
}

TEST(IndexedDynamicArray, SizeConstructor) {
    IT("should create empty IndexDynamicArray with capacity equal to provided size");
    TestArray array{9};
    EXPECT_TRUE(array.isEmpty());
    EXPECT_EQ(array.size(), 0);
    EXPECT_EQ(array.capacity(), 9);
    EXPECT_FALSE(array.isFull());
    EXPECT_FALSE(array.hasElementAt(0));
    TestArray empty{0};
    EXPECT_EQ(empty.size(), 0);
    EXPECT_EQ(empty.capacity(), 0);
    EXPECT_TRUE(empty.isFull());
    EXPECT_FALSE(array.hasElementAt(2));
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
    array.setElement(44, 4);
    array.setElement(32, 2);
    array.setElement(111, 1);
    EXPECT_EQ(array.capacity(), 4);
    EXPECT_EQ(array.size(), 4);
    array.shrinkToFit();
    EXPECT_EQ(array.size(), 4);
    EXPECT_EQ(array.capacity(), 4);
    for(size_t i = 0; i < 9; ++i) {
        array.setElement(10 * i * i + i, i);
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
    array.setElement(11, 9);
    EXPECT_EQ(array.capacity(), 2);
    EXPECT_EQ(array.size(), 1);
    EXPECT_FALSE(array.isEmpty());
    EXPECT_FALSE(array.isFull());
    array.clear();
    EXPECT_TRUE(array.isEmpty());
    EXPECT_EQ(array.size(), 0);
    EXPECT_EQ(array.capacity(), 0);
    EXPECT_TRUE(array.isFull());
    array.setElement(33, 4);
    array.setElement(2, 2);
    array.setElement(29, 1);
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
        array.setElement(1000 * i, i);
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

TEST(IndexedDynamicArray, extend) {
    IT("extends capacity for elements by making a reallocation");
    TestArray array;
    EXPECT_EQ(array.capacity(), 0);
    array.extend(7);
    EXPECT_EQ(array.capacity(), 7);
    array.extend(0);
    EXPECT_EQ(array.capacity(), 7);
    array.clear();
    EXPECT_EQ(array.capacity(), 0);
    array.extend(6);
    EXPECT_EQ(array.capacity(), 6);
}

TEST(IndexedDynamicArray, getElement) {
    IT("returns element at given index, checks for emptiness and invalid index");
    TestArray array;
    EXPECT_FALSE(array.hasElementAt(0));
    array.setElement(7, 9);
    EXPECT_FALSE(array.hasElementAt(0));;
    EXPECT_EQ(array.getElement(7), 9);
    EXPECT_FALSE(array.hasElementAt(1));
    EXPECT_FALSE(array.hasElementAt(9));
    EXPECT_TRUE(array.hasElementAt(7));
    array.clear();
    EXPECT_FALSE(array.hasElementAt(0));
    array.setElement(7623, 9);
    EXPECT_EQ(array.getElement(7623), 9);
    EXPECT_FALSE(array.hasElementAt(76223));
    EXPECT_FALSE(array.hasElementAt(48389));
    EXPECT_FALSE(array.hasElementAt(1405));
}

TEST(IndexedDynamicArray, getFirstElementIndex) {
    IT("returns the first element index if IndexDynamicArray is not empty else throws proper exception");
    TestArray array;
    array.setElement(9, 9);
    EXPECT_EQ(array.getFirstElementIndex(), 9);
    array.setElement(9991, 9);
    EXPECT_EQ(array.getFirstElementIndex(), 9);
    array.removeElement(9991);
    EXPECT_EQ(array.getFirstElementIndex(), 9);
    array.removeElement(9);
    array.setElement(2, 3);
    EXPECT_EQ(array.getFirstElementIndex(), 2);
    array.setElement(3, 9);
    EXPECT_EQ(array.getFirstElementIndex(), 2);
    array.setElement(1001, 1);
    EXPECT_EQ(array.getFirstElementIndex(), 2);
    array.removeElement(2);
    EXPECT_EQ(array.getFirstElementIndex(), 3);
    array.removeElement(3);
    EXPECT_EQ(array.getFirstElementIndex(), 1001);
}

TEST(IndexedDynamicArray, getLastElementIndex) {
    IT("returns the last element index if IndexDynamicArray is not empty else throws proper exception");
    TestArray array;
    array.setElement(9, 9);
    EXPECT_EQ(array.getLastElementIndex(), 9);
    array.setElement(9991, -9);
    EXPECT_EQ(array.getLastElementIndex(), 9991);
    array.setElement(9990, 99);
    EXPECT_EQ(array.getLastElementIndex(), 9991);
    array.removeElement(9991);
    EXPECT_EQ(array.getLastElementIndex(), 9990);
    array.removeElement(9);
    array.removeElement(9990);
    array.setElement(2, 3);
    EXPECT_EQ(array.getLastElementIndex(), 2);
    array.setElement(3, 9);
    EXPECT_EQ(array.getLastElementIndex(), 3);
    array.setElement(1001, 1);
    EXPECT_EQ(array.getLastElementIndex(), 1001);
    array.setElement(0, 0);
    EXPECT_EQ(array.getLastElementIndex(), 1001);
    array.setElement(1002, 0);
    EXPECT_EQ(array.getLastElementIndex(), 1002);
}

TEST(IndexedDynamicArray, setElement) {
    IT("sets element at given index if index is found element is replaced else new element is added and array is sorted by element's index");
    TestArray array;
    array.setElement(2, 2);
    EXPECT_TRUE(array.hasElementAt(2));
    EXPECT_EQ(array.getElement(2), 2);
    array.setElement(4, 5);
    array.setElement(6, 1);
    EXPECT_TRUE(array.hasElementAt(4));
    EXPECT_TRUE(array.hasElementAt(6));
    EXPECT_EQ(array.getElement(6), 1);
    EXPECT_EQ(array.getElement(4), 5);
    array.setElement(6, 9);
    EXPECT_EQ(array.getElement(6), 9);
    EXPECT_EQ(array.getElement(4), 5);
    array.setElement(4, 2);
    EXPECT_EQ(array.getElement(4), 2);
}

TEST(IndexedDynamicArray, isEmpty) {
    IT("returns true if IndexedDynamicArray's size is equal to 0");
    TestArray array;
    EXPECT_TRUE(array.isEmpty());
    array.setElement(100, 9);
    EXPECT_FALSE(array.isEmpty());
}

TEST(IndexedDynamicArray, isFull) {
    IT("returns true if IndexedDynamicArray's size is equal to it's capacity");
    TestArray array;
    EXPECT_TRUE(array.isFull());
    array.setElement(100, 9);
    EXPECT_FALSE(array.isFull());
    EXPECT_EQ(array.size(), 1);
    EXPECT_EQ(array.capacity(), 2);
    array.setElement(3, 3);
    EXPECT_TRUE(array.isFull());
    EXPECT_EQ(array.size(), 2);
    EXPECT_EQ(array.capacity(), 2);
    array.setElement(9999, -100);
    EXPECT_FALSE(array.isFull());
    EXPECT_EQ(array.size(), 3);
    EXPECT_EQ(array.capacity(), 6);
}

TEST(IndexedDynamicArray, size) {
    IT("returns the count of elements in the IndxedDynamicArray");
    TestArray array;
    EXPECT_EQ(array.size(), 0);
    array.setElement(3, 9);
    EXPECT_EQ(array.size(), 1);
    array.setElement(100, 4);
    array.setElement(22, 231);
    EXPECT_EQ(array.size(), 3);
    for(size_t i = 0; i < 11; ++i) {
        array.setElement(2 * i, i);
    }
    EXPECT_EQ(array.size(), 14);
}

TEST(IndexedDynamicArray, capacity) {
    IT("returns the size of dynamically allocated memory for the IndexedDynamicArray's elements");
    TestArray array;
    EXPECT_EQ(array.size(), 0);
    array.setElement(3, 9);
    EXPECT_EQ(array.capacity(), 2);
    array.setElement(100, 4);
    array.setElement(231, 22);
    EXPECT_EQ(array.capacity(), 6);
    for(size_t i = 0; i < 11; ++i) {
        array.setElement(2 * i, i);
    }
    EXPECT_EQ(array.size(), 14);
    EXPECT_EQ(array.capacity(), 14);
    EXPECT_TRUE(array.isFull());
    array.setElement(43583, -342);
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
    array.setElement(222, -222);
    array.setElement(13, 9);
    array.setElement(96, 7);
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
    copy.setElement(19348, -111);
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
    array.setElement(222, -222);
    array.setElement(13, 9);
    array.setElement(96, 7);
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
    array.setElement(222, -222);
    array.setElement(13, 9);
    array.setElement(96, 7);
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
    copy.setElement(19348, -111);
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
    array.setElement(222, -222);
    array.setElement(13, 9);
    array.setElement(96, 7);
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

    TestArray array{10};
    array.setElement(45, 1);
    array.setElement(454, 6);
    array.setElement(2, 3);
    array.setElement(13, 6);
    array.setElement(42, 22);
    array.setElement(53, 9549);
    array.setElement(678, -343);
    array.setElement(17, 123);
    array.setElement(81, 5);
    array.setElement(9999, 971);

    size_t position = 0;
    const int data[10] = {3, 6, 123, 22, 1, 9549, 5, 6, -343, 971};
    const size_t indexes[10] = {2, 13, 17, 42, 45, 53, 81, 454, 678, 9999};

    array.forEach([&data, &indexes, &position](int element, size_t index) {
        EXPECT_EQ(element, data[position]);
        EXPECT_EQ(index, indexes[position]);
        ++position;
    });

    EXPECT_EQ(position, 10);

    int sum = 0;
    array.forEach([&sum](int element, size_t) {
        sum += element;
    });

    EXPECT_EQ(sum, 10343);
}