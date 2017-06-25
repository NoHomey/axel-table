#include "Reader.h"
#include "gtest/gtest.h"
#include "../../It/It.h"

#include <iostream>

TEST(Reader, readNewlineTerminatedBlock) {
    IT("reads (dummy test)");

    FILE* fd = std::fopen("./../IO/Reader/test.txt", "r");
    std::cout << "opened: " << (fd == nullptr ? "No" : "Yes") << std::endl;
    std::cout << "Chunks ------------------------------------------------" << std::endl;
    Reader reader{fd};
    for(int i  = 0; i < 3; ++i) {
        Reader::NewlineBlock block = reader.readNewlineTerminatedBlock();
        const char* data = block.data();
        const size_t size = block.size();
        for(size_t i = 0; i < size; ++i) {
            std::cout << data[i];
        }
        std::cout << std::endl << "CHUCK size: " << size << std::endl;
    }
    std::fclose(fd);
}