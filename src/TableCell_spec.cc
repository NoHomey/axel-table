#include <limits.h>
#include "gtest/gtest.h"
#include "TableCell.h"

TEST(TableCell, NewCell) {
	TableCell cell;
	EXPECT_TRUE(cell.isEmpty());
}
