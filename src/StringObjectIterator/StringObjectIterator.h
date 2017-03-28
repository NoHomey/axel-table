#pragma once

#include "../StringObject/StringObject.h"

class StringObjectIterator {
public:
    StringObjectIterator(const StringObject& string) noexcept;

    StringObjectIterator(const StringObjectIterator& other) = delete;

    StringObjectIterator& operator=(const StringObjectIterator& other) = delete;

    void next() noexcept;

    /*void prev() noexcept;

    void iterate(const StringObject& string) noexcept;

    void reset() noexcept;

    char current() const noexcept;

    bool endReached() const noexcept;*/

    bool isMoved() const noexcept;

    const StringObject& getIterated() const noexcept;

    const char* getPosition() const noexcept;

protected:
    const StringObject& iterated;
    const char* position;
};