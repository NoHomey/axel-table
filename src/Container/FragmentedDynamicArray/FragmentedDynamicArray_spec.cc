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