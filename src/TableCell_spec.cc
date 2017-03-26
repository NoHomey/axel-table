#include <limits.h>
#include "gtest/gtest.h"
#include "TableCell.h"
#include "It.h"

TEST(TableCell, NewCell) {
	IT("should be empty");
	TableCell cell;
	EXPECT_TRUE(cell.isEmpty());
	EXPECT_FALSE(cell.isInteger());
	EXPECT_FALSE(cell.isDouble());
	EXPECT_FALSE(cell.isString());
	EXPECT_FALSE(cell.isError());
}

TEST(TableCell, NewIntegerCell) {
	IT("should become Integer cell when construted with int");
	TableCell cell = 9;
	EXPECT_FALSE(cell.isEmpty());
	EXPECT_TRUE(cell.isInteger());
	EXPECT_FALSE(cell.isDouble());
	EXPECT_FALSE(cell.isString());
	EXPECT_FALSE(cell.isError());
}
