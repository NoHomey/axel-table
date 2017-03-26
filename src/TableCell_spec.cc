#include <limits.h>
#include "gtest/gtest.h"
#include "TableCell.h"
#include "It.h"

TEST(TableCell, NewCell) {
	IT("should be empty");
	TableCell cell;
	EXPECT_TRUE(cell.isEmpty());
}
