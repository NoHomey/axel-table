#include "InputString.h"
#include "gtest/gtest.h"
#include "../../It/It.h"

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
    EXPECT_EQ(str.getIndexOfLastNewline(), 13);
}

TEST(InputString, getIndexOfLastNewline) {
    IT("returns the index of last found new line char or length() if none is found");

    {
        InputString str{9};
        char* buffer = str.obtainBufferForInput();

        for(int i = 0; i < 9; ++i) {
            buffer[i] = '\n';
        }
        buffer[9] = '\0';
        str.syncSize(9);

        EXPECT_EQ(str.length(), 9);
        EXPECT_EQ(str.getIndexOfLastNewline(), 8);
    }

    {
        InputString str{9};
        char* buffer = str.obtainBufferForInput();
        
        buffer[0] = 'S';
        buffer[1] = 'o';
        buffer[2] = 'm';
        buffer[3] = 'e';
        buffer[4] = ' ';
        buffer[5] = 't';
        buffer[6] = 'e';
        buffer[7] = 'x';
        buffer[8] = 't';
        buffer[9] = '\0';

        str.syncSize(9);

        EXPECT_EQ(str.length(), 9);
        EXPECT_EQ(str.getIndexOfLastNewline(), 9);
    }

    {
        InputString str{14};
        char* buffer = str.obtainBufferForInput();
        
        buffer[0] = 'S';
        buffer[1] = 'o';
        buffer[2] = 'm';
        buffer[3] = 'e';
        buffer[4] = ' ';
        buffer[5] = 't';
        buffer[6] = 'e';
        buffer[7] = 'x';
        buffer[8] = 't';
        buffer[9] = '\n';
        buffer[10] = '.';
        buffer[11] = '.';
        buffer[12] = '.';
        buffer[13] = '\n';
        buffer[14] = '\0';

        str.syncSize(14);

        EXPECT_EQ(str.length(), 14);
        EXPECT_EQ(str.getIndexOfLastNewline(), 13);
    }

    {
        InputString str{22};
        char* buffer = str.obtainBufferForInput();
        
        buffer[0] = 'S';
        buffer[1] = 'o';
        buffer[2] = 'm';
        buffer[3] = 'e';
        buffer[4] = ' ';
        buffer[5] = 't';
        buffer[6] = 'e';
        buffer[7] = 'x';
        buffer[8] = 't';
        buffer[9] = '\n';
        buffer[10] = '.';
        buffer[11] = '.';
        buffer[12] = '.';
        buffer[13] = '\n';
        buffer[14] = 'W';
        buffer[15] = 'a';
        buffer[16] = 's';
        buffer[17] = ' ';
        buffer[18] = 't';
        buffer[19] = 'h';
        buffer[20] = 'i';
        buffer[21] = 's';
        buffer[22] = '\0';

        str.syncSize(22);

        EXPECT_EQ(str.length(), 22);
        EXPECT_EQ(str.getIndexOfLastNewline(), 13);
    }
}