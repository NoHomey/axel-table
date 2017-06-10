#include "DynamicArray.htd"
#include "gtest/gtest.h"
#include "../It/It.h"

template class DynamicArray<int>;
using Array = DynamicArray<int>;

TEST(DynamicArray, DefaultConstructor) {
    IT("should create empty array");
    Array array;
    EXPECT_TRUE(array.isEmpty());
    EXPECT_EQ(array.size(), 0);
    EXPECT_EQ(array.capacity(), 0);
}
