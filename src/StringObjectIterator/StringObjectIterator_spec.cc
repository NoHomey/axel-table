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

TEST(StringObjectIterator, next) {
    IT("advances the iterator to point to the enxt symbol");
    StringObject str = {"text"};
    StringObjectIterator it = {str};
    EXPECT_EQ(it.getPosition(), str.cString());
    it.next();
    EXPECT_NE(it.getPosition(), str.cString());
    EXPECT_EQ(it.getPosition(), str.cString() + 1);
}


TEST(StringObjectIterator, isMoved) {
    IT("checks if iterator has been moved forward from it's logical begining");
    StringObjectIterator it = {{"text"}};
    EXPECT_FALSE(it.isMoved());
    it.next();
    EXPECT_TRUE(it.isMoved());
}