#include <limits.h>
#include "gtest/gtest.h"
#include "TableCell.h"
#include "It.h"

TEST(TableCell, NewTableCell) {
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

TEST(TableCell, NewDoubleCell) {
	IT("should become Double cell when construted with double");
	TableCell cell = 3.7;
	EXPECT_FALSE(cell.isEmpty());
	EXPECT_FALSE(cell.isInteger());
	EXPECT_TRUE(cell.isDouble());
	EXPECT_FALSE(cell.isString());
	EXPECT_FALSE(cell.isError());
}

TEST(TableCell, NewErrorCell) {
	IT("should be an ErrorCell");
	TableCell cell = TableCell::ErrorCell();
	EXPECT_FALSE(cell.isEmpty());
	EXPECT_FALSE(cell.isInteger());
	EXPECT_FALSE(cell.isDouble());
	EXPECT_FALSE(cell.isString());
	EXPECT_TRUE(cell.isError());
}

TEST(TableCell, toIntegerWhenTableCellisEmpty) {
	IT("should return 0 if TableCell isEmpty");
	TableCell cell;
	EXPECT_EQ(cell.toInteger(), 0);
}

TEST(TableCell, toIntegerWhenTableCellisInteger) {
	IT("should return value with which it was constructed if TableCell isInteger");
	TableCell cell = 9;
	EXPECT_EQ(cell.toInteger(), 9);
}

TEST(TableCell, toIntegerWhenTableCellisError) {
	IT("should return 0 if TableCell isError");
	TableCell cell = TableCell::ErrorCell();
	EXPECT_EQ(cell.toInteger(), 0);
}