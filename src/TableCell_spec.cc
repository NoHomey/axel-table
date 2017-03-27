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
	int values[14] = {9, -1, 4, 7, 12332, 324, 24324, 24, -3424, 564, 256, 1, 0, 42};
	for(size_t i = 0; i < 14; ++i) {
		TableCell cell1 = values[i];
		EXPECT_EQ(cell1.toInteger(), values[i]);
	}
}

TEST(TableCell, toIntegerWhenTableCellisDouble) {
	IT("should return value rounded to nearest int with which it was constructed if TableCell isDouble");
	double values[14] = {9, -1, 4.2, 7.3, 12332.69, 324.82, 24324.003, 24.2, -3424.5, 564.12, 256.99, 1.5679, 0, -42.3};
	int expects[14] = {9, -1, 4, 7, 12332, 324, 24324, 24, -3424, 564, 256, 1, 0, -42};
	for(size_t i = 0; i < 14; ++i) {
		TableCell cell1 = values[i];
		EXPECT_EQ(cell1.toInteger(), expects[i]);
	}
}

TEST(TableCell, toIntegerWhenTableCellisError) {
	IT("should return 0 if TableCell isError");
	TableCell cell = TableCell::ErrorCell();
	EXPECT_EQ(cell.toInteger(), 0);
}