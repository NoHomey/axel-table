#include "Reader.h"
#include "gtest/gtest.h"
#include "../../It/It.h"

#include <iostream>

TEST(Reader, readNewlineTerminatedBlock) {
    IT("reads (dummy test)");

    FILE* fd = std::fopen("./../IO/Reader/test.txt", "r");
    std::cout << "opened: " << (fd == nullptr ? "No" : "Yes") << std::endl;
    InputStream inputStream{fd};
    Reader reader{inputStream};
    std::cout << "Chunks ------------------------------------------------" << std::endl;
    while(true) {
        Reader::NewlineBlock block = reader.readNewlineTerminatedBlock();
        const size_t size = block.size();
        if(size == 0) {
            break;
        }
        const char* data = block.data();
        for(size_t i = 0; i < size; ++i) {
            std::cout << data[i];
        }
        std::cout << std::endl << "CHUCK size: " << size << std::endl;
    }
    std::fclose(fd);
}