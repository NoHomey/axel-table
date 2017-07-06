#pragma once

#include "../MOCKABLE.mcrs"
#include <cstdio>

class InputStream {
public:
    InputStream(FILE* fileObject) noexcept;

    MOCKABLE size_t read(char* buffer, size_t count);

    MOCKABLE bool isEndOfFileReached() const noexcept;

 protected:
    FILE* filePtr;   
};