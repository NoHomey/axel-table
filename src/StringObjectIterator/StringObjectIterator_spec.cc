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
    IT("advances the iterator to point to the next meaning symbol");
    StringObject str = {"text"};
    StringObjectIterator it = {str};
    EXPECT_EQ(it.getPosition(), str.cString());
    it.next();
    EXPECT_NE(it.getPosition(), str.cString());
    EXPECT_EQ(it.getPosition(), str.cString() + 1);
    it.next();
    EXPECT_EQ(it.getPosition(), str.cString() + 2);
    it.next();
    EXPECT_EQ(it.getPosition(), str.cString() + 3);
    it.next();
    EXPECT_EQ(it.getPosition(), str.cString() + 4);
    it.next();
    it.next();
    it.next();
    it.next();
    EXPECT_EQ(it.getPosition(), str.cString() + 4);
}

TEST(StringObjectIterator, nextWhenNull) {
    IT("donse not advances if StringObject isNull");
    StringObject str;
    StringObjectIterator it = {str};
    EXPECT_EQ(it.getPosition(), str.cString());
    for(int i = 0; i < 10; ++i) {
        it.next();
        it.next();
        it.next();
        EXPECT_EQ(it.getPosition(), str.cString());
    }
}

TEST(StringObjectIterator, isMoved) {
    IT("checks if iterator has been moved forward from it's logical begining");
    StringObjectIterator it = {"txt"};
    EXPECT_FALSE(it.isMoved());
    it.next();
    EXPECT_TRUE(it.isMoved());
    it.next();
    EXPECT_TRUE(it.isMoved());
    it.next();
    EXPECT_TRUE(it.isMoved());
    it.next();
    EXPECT_TRUE(it.isMoved());
    it.next();
    EXPECT_TRUE(it.isMoved());
}

TEST(StringObjectIterator, isMovedWhenNull) {
    IT("if StringObject isNull, isMove will return false");
    StringObjectIterator it = {{}};
    for(int i = 0; i < 23; ++i) {
        EXPECT_FALSE(it.isMoved());
    }
}

TEST(StringObjectIterator, isEndReachedWhenNull) {
    IT("if StringObject isNull caling isEndReached() should return true and isMoved false");
    StringObjectIterator it = {{}};
    for(int i = 0; i < 10; ++i) {
        it.next();
        it.next();
        it.next();
        EXPECT_TRUE(it.isEndReached());
        EXPECT_FALSE(it.isMoved());
    }
}

TEST(StringObjectIterator, isEndReached) {
    IT("returns true when End is reached and false if not");
    StringObject str = {"0123456789"};
    StringObjectIterator it = {str};
    EXPECT_FALSE(it.isEndReached());
    for(int i = 0; i < 9; ++i) {
        it.next();
        EXPECT_FALSE(it.isEndReached());
    }
    for(int i = 0; i < 10; ++i) {
        it.next();
        EXPECT_TRUE(it.isEndReached());
    }
}