#include "InputStream.h"

InputStream::InputStream(FILE* fileObject) noexcept
: filePtr{fileObject} { }

bool InputStream::isEndOfFileReached() const noexcept {
    return std::feof(filePtr) != 0;
}

size_t InputStream::read(char* buffer, size_t count) {
    return std::fread(buffer, sizeof(char), count, filePtr);
}