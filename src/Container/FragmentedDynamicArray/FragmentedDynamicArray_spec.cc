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
    array.setElement(9, 0);
    EXPECT_FALSE(array.isEmpty());
    array.setElement(-823, 1);
    EXPECT_FALSE(array.isEmpty());
    TestArray array2;
    EXPECT_TRUE(array2.isEmpty());
    array2.setElement(9, 999);
    EXPECT_FALSE(array2.isEmpty());
    array2.setElement(1823, 2);
    EXPECT_FALSE(array2.isEmpty());
}

TEST(FragmentedDynamicArray, isFull) {
    IT("returns true if FragmentedDynamicArray's size is equal to it's capacity");
    TestArray array;
    EXPECT_TRUE(array.isFull());
    array.setElement(9, 0);
    EXPECT_FALSE(array.isFull());
    EXPECT_EQ(array.size(), 1);
    EXPECT_EQ(array.capacity(), 2);
    array.setElement(3, 1);
    EXPECT_TRUE(array.isFull());
    EXPECT_EQ(array.size(), 2);
    EXPECT_EQ(array.capacity(), 2);
    array.setElement(100, 2);
    EXPECT_FALSE(array.isFull());
    EXPECT_EQ(array.size(), 3);
    EXPECT_EQ(array.capacity(), 6);
}

TEST(FragmentedDynamicArray, size) {
    IT("returns the count of elements in the FragmentedDynamicArray");
    TestArray array;
    EXPECT_EQ(array.size(), 0);
    array.setElement(9, 0);
    EXPECT_EQ(array.size(), 1);
    array.setElement(4, 1);
    EXPECT_EQ(array.size(), 2);
    for(size_t i = 0; i < 9; ++i) {
        array.setElement(i, i + 2);
    }
    EXPECT_EQ(array.size(), 11);
    array.setElement(12, 100);
    EXPECT_EQ(array.size(), 12);
    array.setElement(-100, 10000);
    EXPECT_EQ(array.size(), 13);
    array.setElement(-10000, 14546);
    EXPECT_EQ(array.size(), 14);
    array.setElement(1, 14);
    EXPECT_EQ(array.size(), 15);
}

TEST(FragmentedDynamicArray, capacity) {
    IT("returns the size of dynamically allocated memory for the FragmentedDynamicArray's elements");
    TestArray array;
    EXPECT_EQ(array.capacity(), 0);
    array.setElement(9, 0);
    EXPECT_EQ(array.capacity(), 2);
    array.setElement(4, 1);
    EXPECT_EQ(array.capacity(), 2);
    for(size_t i = 0; i < 9; ++i) {
        array.setElement(i, i + 2);
    }
    EXPECT_EQ(array.capacity(), 14);
    array.setElement(12, 100);
    EXPECT_EQ(array.capacity(), 16);
    array.setElement(-100, 10000);
    EXPECT_EQ(array.capacity(), 16);
    array.setElement(-10000, 14546);
    EXPECT_EQ(array.capacity(), 20);
    array.setElement(1, 14);
    EXPECT_EQ(array.capacity(), 20);
}

TEST(FragmentedDynamicArray, setElement) {
    IT("sets element at given index if index is found element is replaced else new element is added and array is sorted by element's index");
    TestArray array;
    array.setElement(7, 0);
    EXPECT_FALSE(array.isEmpty());
    EXPECT_EQ(array.size(), 1);
    EXPECT_EQ(array.capacity(), 2);
    EXPECT_FALSE(array.isFull());
    EXPECT_EQ(array[0], 7);
    array.setElement(9, 1);
    EXPECT_FALSE(array.isEmpty());
    EXPECT_EQ(array.size(), 2);
    EXPECT_EQ(array.capacity(), 2);
    EXPECT_TRUE(array.isFull());
    EXPECT_EQ(array[0], 7);
    EXPECT_EQ(array[1], 9);
    array.setElement(9, 1);
    EXPECT_FALSE(array.isEmpty());
    EXPECT_EQ(array.size(), 2);
    EXPECT_EQ(array.capacity(), 2);
    EXPECT_TRUE(array.isFull());
    EXPECT_EQ(array[0], 7);
    EXPECT_EQ(array[1], 9);
    array.setElement(100, 3);
    EXPECT_FALSE(array.isEmpty());
    EXPECT_EQ(array.size(), 3);
    EXPECT_EQ(array.capacity(), 4);
    EXPECT_FALSE(array.isFull());
    EXPECT_EQ(array[0], 7);
    EXPECT_EQ(array[1], 9);
    EXPECT_THROW(array[2], ::IndexNotFound);
    EXPECT_EQ(array[3], 100);
    array.setElement(99, 2);
    EXPECT_FALSE(array.isEmpty());
    EXPECT_EQ(array.size(), 4);
    EXPECT_EQ(array.capacity(), 8);
    EXPECT_FALSE(array.isFull());
    EXPECT_EQ(array[0], 7);
    EXPECT_EQ(array[1], 9);
    EXPECT_EQ(array[2], 99);
    EXPECT_EQ(array[3], 100);
    array.setElement(8, 7);
    EXPECT_FALSE(array.isEmpty());
    EXPECT_EQ(array.size(), 5);
    EXPECT_EQ(array.capacity(), 8);
    EXPECT_FALSE(array.isFull());
    EXPECT_EQ(array[0], 7);
    EXPECT_EQ(array[1], 9);
    EXPECT_EQ(array[2], 99);
    EXPECT_EQ(array[3], 100);
    EXPECT_THROW(array[4], ::IndexNotFound);
    EXPECT_THROW(array[5], ::IndexNotFound);
    EXPECT_THROW(array[6], ::IndexNotFound);
    EXPECT_EQ(array[7], 8);
    array.setElement(-344, 4);
    array.setElement(-23445, 5);
    array.setElement(9341, 6);
    EXPECT_EQ(array[0], 7);
    EXPECT_EQ(array[1], 9);
    EXPECT_EQ(array[2], 99);
    EXPECT_EQ(array[3], 100);
    EXPECT_EQ(array[4], -344);
    EXPECT_EQ(array[5], -23445);
    EXPECT_EQ(array[6], 9341);
    EXPECT_EQ(array[7], 8);
    EXPECT_FALSE(array.isEmpty());
    EXPECT_EQ(array.size(), 8);
    EXPECT_EQ(array.capacity(), 12);
    EXPECT_FALSE(array.isFull());
    array.setElement(0, 1);
    array.setElement(991, 4);
    array.setElement(111456, 7);
    EXPECT_EQ(array[0], 7);
    EXPECT_EQ(array[1], 0);
    EXPECT_EQ(array[2], 99);
    EXPECT_EQ(array[3], 100);
    EXPECT_EQ(array[4], 991);
    EXPECT_EQ(array[5], -23445);
    EXPECT_EQ(array[6], 9341);
    EXPECT_EQ(array[7], 111456);
    EXPECT_FALSE(array.isEmpty());
    EXPECT_EQ(array.size(), 8);
    EXPECT_EQ(array.capacity(), 12);
    EXPECT_FALSE(array.isFull());
}

TEST(FragmentedDynamicArray, removeElement) {
    IT("removes the element at the given index if such index is found else it throws exception");
    TestArray array;
    EXPECT_TRUE(array.isEmpty());
    EXPECT_EQ(array.size(), 0);
    EXPECT_EQ(array.capacity(), 0);
    EXPECT_TRUE(array.isFull());
    EXPECT_THROW(array.removeElement(0), ::EmptyDynamicArray);
    EXPECT_THROW(array.removeElement(6), ::EmptyDynamicArray);
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
    EXPECT_TRUE(array.isEmpty());
    EXPECT_EQ(array.size(), 0);
    EXPECT_EQ(array.capacity(), 2);
    EXPECT_FALSE(array.isFull());
    array.setElement(2, 2);
    array.setElement(3, 3);
    EXPECT_FALSE(array.isEmpty());
    EXPECT_EQ(array.size(), 2);
    EXPECT_EQ(array.capacity(), 2);
    EXPECT_TRUE(array.isFull());
    array.setElement(0, 0);
    EXPECT_FALSE(array.isEmpty());
    EXPECT_EQ(array.size(), 3);
    EXPECT_EQ(array.capacity(), 4);
    EXPECT_FALSE(array.isFull());
    array.setElement(1, 1);
    EXPECT_FALSE(array.isEmpty());
    EXPECT_EQ(array.size(), 4);
    EXPECT_EQ(array.capacity(), 4);
    EXPECT_TRUE(array.isFull());
    EXPECT_EQ(array[0], 0);
    EXPECT_EQ(array[1], 1);
    EXPECT_EQ(array[2], 2);
    EXPECT_EQ(array[3], 3);
    EXPECT_THROW(array.removeElement(0), ::OperationNotPermitted);
    EXPECT_NO_THROW(array.removeElement(1));
    EXPECT_FALSE(array.isEmpty());
    EXPECT_EQ(array.size(), 3);
    EXPECT_EQ(array.capacity(), 4);
    EXPECT_FALSE(array.isFull());
    EXPECT_NO_THROW(array.removeElement(0));
    EXPECT_FALSE(array.isEmpty());
    EXPECT_EQ(array.size(), 2);
    EXPECT_EQ(array.capacity(), 4);
    EXPECT_FALSE(array.isFull());
    EXPECT_NO_THROW(array.removeElement(2));
    EXPECT_NO_THROW(array.removeElement(3));
    EXPECT_TRUE(array.isEmpty());
    EXPECT_EQ(array.size(), 0);
    EXPECT_EQ(array.capacity(), 4);
    EXPECT_FALSE(array.isFull());
    EXPECT_THROW(array.removeElement(10), ::EmptyDynamicArray);
    EXPECT_THROW(array.removeElement(1), ::EmptyDynamicArray);
    EXPECT_THROW(array.removeElement(0), ::EmptyDynamicArray);
}

TEST(FragmentedDynamicArray, indexOperator) {
    IT("returns element at the given index, checks for emptiness and invalid index");
    TestArray array;
    EXPECT_THROW(array[0], ::EmptyDynamicArray);
    EXPECT_THROW(array[100], ::EmptyDynamicArray);
    for(size_t i = 0; i < 9; ++i) {
        array.setElement(i, i);
    }
    for(size_t i = 0; i < 9; ++i) {
        EXPECT_EQ(array[i], i);
    }
    EXPECT_THROW(array[99], ::IndexNotFound);
    EXPECT_THROW(array[100], ::IndexNotFound);
    array.setElement(100, 99);
    array.setElement(99, 100);
    EXPECT_EQ(array[99], 100);
    EXPECT_EQ(array[100], 99);
}

TEST(FragmentedDynamicArray, getElement) {
    IT("returns element at given index, checks for emptiness and invalid index");
    TestArray array;
    EXPECT_THROW(array.getElement(0), ::EmptyDynamicArray);
    EXPECT_THROW(array.getElement(100), ::EmptyDynamicArray);
    for(size_t i = 0; i < 9; ++i) {
        array.setElement(i, i);
    }
    for(size_t i = 0; i < 9; ++i) {
        EXPECT_EQ(array.getElement(i), i);
    }
    EXPECT_THROW(array.getElement(99), ::IndexNotFound);
    EXPECT_THROW(array.getElement(100), ::IndexNotFound);
    array.setElement(100, 99);
    array.setElement(99, 100);
    EXPECT_EQ(array.getElement(99), 100);
    EXPECT_EQ(array.getElement(100), 99);
}

TEST(FragmentedDynamicArray, getFirstElementIndexWhenCenterIsNotEmpty) {
    IT("returns 0");

    TestArray array;
    array.setElement(1, 0);
    EXPECT_EQ(array.getFirstElementIndex(), 0);
    array.setElement(-1, 1);
    EXPECT_EQ(array.getFirstElementIndex(), 0);
    array.setElement(3, 2);
    EXPECT_EQ(array.getFirstElementIndex(), 0);
    array.setElement(1, 10);
    EXPECT_EQ(array.getFirstElementIndex(), 0);
    array.setElement(1, 98);
    EXPECT_EQ(array.getFirstElementIndex(), 0);
    array.setElement(1, 89);
    EXPECT_EQ(array.getFirstElementIndex(), 0);
    array.setElement(1, 3);
    EXPECT_EQ(array.getFirstElementIndex(), 0);
}

TEST(FragmentedDynamicArray, getFirstElementIndexWhenCenterIsEmpty) {
    IT("returns first element index in peripheral if it is empty throws exception");

    TestArray array;
    EXPECT_THROW(array.getFirstElementIndex(), ::EmptyDynamicArray);
    array.setElement(-1, 1);
    EXPECT_EQ(array.getFirstElementIndex(), 1);
    array.setElement(3, 2);
    EXPECT_EQ(array.getFirstElementIndex(), 1);
    array.removeElement(1);
    EXPECT_EQ(array.getFirstElementIndex(), 2);
    array.setElement(1, 98);
    EXPECT_EQ(array.getFirstElementIndex(), 2);
    array.setElement(1, 89);
    EXPECT_EQ(array.getFirstElementIndex(), 2);
    array.setElement(1, 3);
    EXPECT_EQ(array.getFirstElementIndex(), 2);
    array.removeElement(2);
    EXPECT_EQ(array.getFirstElementIndex(), 3);
    array.removeElement(3);
    EXPECT_EQ(array.getFirstElementIndex(), 89);
    array.removeElement(89);
    EXPECT_EQ(array.getFirstElementIndex(), 98);
    array.removeElement(98);
    EXPECT_THROW(array.getFirstElementIndex(), ::EmptyDynamicArray);
}

TEST(FragmentedDynamicArray, getLastElementIndexWhenPeripheralIsNotEmpty) {
    IT("returns peripheralElements.getLastElementIndex()");
    TestArray array;
    array.setElement(1, 10);
    EXPECT_EQ(array.getLastElementIndex(), 10);
    array.setElement(-1, 3);
    EXPECT_EQ(array.getLastElementIndex(), 10);
    array.setElement(1, 0);
    array.setElement(-1, 1);
    array.setElement(2, 2);
    array.setElement(3, 3);
    array.setElement(4, 4);
    array.setElement(3, 2000);
    EXPECT_EQ(array.getLastElementIndex(), 2000);
    array.setElement(1, 10000);
    EXPECT_EQ(array.getLastElementIndex(), 10000);
    array.setElement(1, 9881);
    EXPECT_EQ(array.getLastElementIndex(), 10000);
    array.removeElement(10000);
    EXPECT_EQ(array.getLastElementIndex(), 9881);
    array.removeElement(9881);
    EXPECT_EQ(array.getLastElementIndex(), 2000);
    array.setElement(3, 2001);
    EXPECT_EQ(array.getLastElementIndex(), 2001);
    array.removeElement(2001);
    EXPECT_EQ(array.getLastElementIndex(), 2000);
    array.removeElement(2000);
    EXPECT_EQ(array.getLastElementIndex(), 10);
    array.removeElement(10);
    EXPECT_EQ(array.getLastElementIndex(), 4);
}

TEST(FragmentedDynamicArray, getLastElementIndexWhenPeripheralIsEmpty) {
    IT("returns size() - 1 if it is empty throws exception");

    TestArray array;
    EXPECT_THROW(array.getLastElementIndex(), ::EmptyDynamicArray);
    array.setElement(-1, 0);
    EXPECT_EQ(array.size(), 1);
    EXPECT_EQ(array.getLastElementIndex(), 0);
    array.setElement(3, 1);
    EXPECT_EQ(array.size(), 2);
    EXPECT_EQ(array.getLastElementIndex(), 1);
    array.removeElement(1);
    EXPECT_EQ(array.size(), 1);
    EXPECT_EQ(array.getLastElementIndex(), 0);
    array.setElement(1, 1);
    array.setElement(1, 2);
    EXPECT_EQ(array.size(), 3);
    EXPECT_EQ(array.getLastElementIndex(), 2);
    array.setElement(-344, 3);
    array.setElement(-3414, 4);
    array.setElement(-3442, 5);
    EXPECT_EQ(array.size(), 6);
    EXPECT_EQ(array.getLastElementIndex(), 5);
    array.setElement(31, 6);
    EXPECT_EQ(array.size(), 7);
    EXPECT_EQ(array.getLastElementIndex(), 6);
    array.removeElement(6);
    EXPECT_EQ(array.size(), 6);
    EXPECT_EQ(array.getLastElementIndex(), 5);
    EXPECT_EQ(array.getLastElementIndex(), 5);
    array.removeElement(5);
    EXPECT_EQ(array.size(), 5);
    EXPECT_EQ(array.getLastElementIndex(), 4);
    array.removeElement(4);
    array.removeElement(3);
    EXPECT_EQ(array.size(), 3);
    EXPECT_EQ(array.getLastElementIndex(), 2);
    array.clear();
    EXPECT_THROW(array.getLastElementIndex(), ::EmptyDynamicArray);
}

TEST(FragmentedDynamicArray, clear) {
    IT("clears the FragmentedDynamicArray content and resets size and capacity");
    TestArray array;
    EXPECT_TRUE(array.isEmpty());
    array.setElement(9, 0);
    EXPECT_EQ(array.capacity(), 2);
    EXPECT_EQ(array.size(), 1);
    EXPECT_FALSE(array.isEmpty());
    EXPECT_FALSE(array.isFull());
    array.clear();
    EXPECT_TRUE(array.isEmpty());
    EXPECT_EQ(array.size(), 0);
    EXPECT_EQ(array.capacity(), 0);
    EXPECT_TRUE(array.isFull());
    array.setElement(4, 0);
    array.setElement(2, 1);
    array.setElement(1, 2);
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
        array.setElement(i * i, i);
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
    array.setElement(99, 0);
    array.setElement(1, 100);
    EXPECT_FALSE(array.isEmpty());
    EXPECT_EQ(array.size(), 2);
    EXPECT_EQ(array.capacity(), 4);
    EXPECT_FALSE(array.isFull());
    array.clear();
    EXPECT_TRUE(array.isEmpty());
    EXPECT_EQ(array.size(), 0);
    EXPECT_EQ(array.capacity(), 0);
    EXPECT_TRUE(array.isFull());
    array.setElement(34, 3983);
    array.setElement(3439, 3034);
    EXPECT_FALSE(array.isEmpty());
    EXPECT_EQ(array.size(), 2);
    EXPECT_EQ(array.capacity(), 2);
    EXPECT_TRUE(array.isFull());
    array.clear();
    EXPECT_TRUE(array.isEmpty());
    EXPECT_EQ(array.size(), 0);
    EXPECT_EQ(array.capacity(), 0);
    EXPECT_TRUE(array.isFull());
}

TEST(FragmentedDynamicArray, shrinkToFit) {
    IT("if not full allocates new FragmentedDynamicArray with capacity equal to size the copy all elements, dealocates old memory and moves assigns it");
    TestArray array;
    EXPECT_TRUE(array.isEmpty());
    array.setElement(9, 0);
    EXPECT_EQ(array.capacity(), 2);
    EXPECT_EQ(array.size(), 1);
    EXPECT_FALSE(array.isEmpty());
    EXPECT_FALSE(array.isFull());
    array.shrinkToFit();
    EXPECT_FALSE(array.isEmpty());
    EXPECT_EQ(array.size(), 1);
    EXPECT_EQ(array.capacity(), 1);
    EXPECT_TRUE(array.isFull());
    array.setElement(4, 0);
    array.setElement(2, 1);
    array.setElement(1, 2);
    EXPECT_FALSE(array.isEmpty());
    EXPECT_EQ(array.size(), 3);
    EXPECT_EQ(array.capacity(), 4);
    EXPECT_FALSE(array.isFull());
    array.setElement(9, 3);
    EXPECT_FALSE(array.isEmpty());
    EXPECT_EQ(array.size(), 4);
    EXPECT_EQ(array.capacity(), 4);
    EXPECT_TRUE(array.isFull());
    array.shrinkToFit();
    EXPECT_FALSE(array.isEmpty());
    EXPECT_EQ(array.size(), 4);
    EXPECT_EQ(array.capacity(), 4);
    EXPECT_TRUE(array.isFull());
    array.setElement(-1, 1999);
    EXPECT_FALSE(array.isEmpty());
    EXPECT_EQ(array.size(), 5);
    EXPECT_EQ(array.capacity(), 6);
    EXPECT_FALSE(array.isFull());
    array.shrinkToFit();
    EXPECT_FALSE(array.isEmpty());
    EXPECT_EQ(array.size(), 5);
    EXPECT_EQ(array.capacity(), 5);
    EXPECT_TRUE(array.isFull());
    array.setElement(123, 321);
    EXPECT_FALSE(array.isEmpty());
    EXPECT_EQ(array.size(), 6);
    EXPECT_EQ(array.capacity(), 8);
    EXPECT_FALSE(array.isFull());
    array.shrinkToFit();
    EXPECT_FALSE(array.isEmpty());
    EXPECT_EQ(array.size(), 6);
    EXPECT_EQ(array.capacity(), 6);
    EXPECT_TRUE(array.isFull());
    EXPECT_EQ(array[0], 4);
    EXPECT_EQ(array[1], 2);
    EXPECT_EQ(array[2], 1);
    EXPECT_EQ(array[3], 9);
    EXPECT_EQ(array[1999], -1);
    EXPECT_EQ(array[321], 123);
}

TEST(FragmentedDynamicArray, CopyConstructor) {
    IT("should copy other FragmentedDynamicArray and sets capacity and size of the copy equal to other's size");
    TestArray empty;
    TestArray array = empty;
    EXPECT_TRUE(array.isEmpty());
    EXPECT_EQ(array.size(), 0);
    EXPECT_EQ(array.capacity(), 0);
    EXPECT_TRUE(array.isFull());
    array.setElement(2, 0);
    array.setElement(9, 1);
    array.setElement(7, 2);
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
    copy.setElement(-10, 3944);
    copy.setElement(100, 10000);
    EXPECT_FALSE(copy.isEmpty());
    EXPECT_EQ(copy.size(), 5);
    EXPECT_EQ(copy.capacity(), 5);
    EXPECT_TRUE(copy.isFull());
    copy.setElement(99, 99);
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
    array.setElement(2, 0);
    array.setElement(9, 1);
    array.setElement(7, 2);
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
    moved.setElement(-10, 3944);
    moved.setElement(100, 10000);
    EXPECT_FALSE(moved.isEmpty());
    EXPECT_EQ(moved.size(), 5);
    EXPECT_EQ(moved.capacity(), 8);
    EXPECT_FALSE(moved.isFull());
    moved.setElement(99, 99);
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
    array.setElement(2, 0);
    array.setElement(9, 1);
    array.setElement(7, 2);
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
    copy.setElement(-10, 3944);
    copy.setElement(100, 10000);
    EXPECT_FALSE(array.isEmpty());
    EXPECT_EQ(array.size(), 3);
    EXPECT_EQ(array.capacity(), 6);
    EXPECT_FALSE(array.isFull());
    EXPECT_FALSE(copy.isEmpty());
    EXPECT_EQ(copy.size(), 5);
    EXPECT_EQ(copy.capacity(), 5);
    EXPECT_TRUE(copy.isFull());
    copy.setElement(99, 99);
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
    array.setElement(2, 0);
    array.setElement(9, 1);
    array.setElement(7, 2);
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
    moved.setElement(-10, 3944);
    moved.setElement(100, 10000);
    EXPECT_FALSE(moved.isEmpty());
    EXPECT_EQ(moved.size(), 5);
    EXPECT_EQ(moved.capacity(), 8);
    EXPECT_FALSE(moved.isFull());
    moved.setElement(99, 99);
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

TEST(FragmentedDynamicArray, forEach) {
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
        const int data[16] = {-1, 0, 111, 325, 357, 16, 3, 6, 123, 22, 1, 9549, 5, 6, -343, 971};
        const size_t indexes[16] = {0, 1, 2, 3, 4, 5, 6, 13, 17, 42, 45, 53, 81, 454, 678, 9999};
    };

    TestArray array;
    array.setElement(1, 45);
    array.setElement(6, 454);
    array.setElement(3, 6);
    array.setElement(6, 13);
    array.setElement(22, 42);
    array.setElement(9549, 53);
    array.setElement(-343, 678);
    array.setElement(123, 17);
    array.setElement(5, 81);
    array.setElement(971, 9999);
    array.setElement(-1, 0);
    array.setElement(0, 1);
    array.setElement(111, 2);
    array.setElement(325, 3);
    array.setElement(357, 4);
    array.setElement(16, 5);

    Expecter expecter;
    array.forEach(expecter);
}