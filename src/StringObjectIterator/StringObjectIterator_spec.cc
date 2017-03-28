#include "StringObjectIterator.h"
#include "gtest/gtest.h"
#include "../It/It.h"

TEST(StringObjectIterator, ConstructorAndGetters) {
    IT("creates new StringObjectIterator, which position is set to begin of StringObject::cString");
    StringObject str = {"text"};
    StringObjectIterator it = {str};
    EXPECT_EQ(it.getIterated(), str);
    EXPECT_EQ(it.getPosition(), str.cString());
}