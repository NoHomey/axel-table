#include "InputString.h"
#include "gtest/gtest.h"
#include "../../It/It.h"

#include <iostream>

TEST(InputString, InputString) {
    IT("can return mutable buffer and sync it size after mutation");

    InputString str{13};

    EXPECT_TRUE(str.isEmpty());
    EXPECT_EQ(str.length(), 0);
    EXPECT_EQ(str.capacity(), 13);
    EXPECT_NE(str.cString(), nullptr);

    char* buffer = str.obtainBufferForInput();
    EXPECT_EQ(buffer, str.cString());

    buffer[0] = 'W';
    buffer[1] = 'r';
    buffer[2] = 'i';
    buffer[3] = 't';
    buffer[4] = 'i';
    buffer[5] = 'n';
    buffer[6] = 'g';
    buffer[7] = ' ';
    buffer[8] = 'i';
    buffer[9] = 'n';
    buffer[10] = ' ';
    buffer[11] = 'i';
    buffer[12] = 't';
    buffer[13] = '\0';

    str.syncSize(13);

    EXPECT_EQ(str.length(), 13);
    EXPECT_EQ(str.obtainBufferForInput(), str.cString());
    EXPECT_EQ(str, DynamicString{"Writing in it"});
}