#pragma once

#include "../StringObject/StringObject.h"

class StringObjectIterator {
public:
    StringObjectIterator(const StringObject& string) noexcept;

    StringObjectIterator(const StringObjectIterator& other) = delete;

    StringObjectIterator& operator=(const StringObjectIterator& other) = delete;

    /*void iterate(const StringObject& string) noexcept;

    void reset() noexcept;

    void next() noexcept;

    void prev() noexcept;

    char current() const noexcept;

    bool endReached() const noexcept;

    bool isMoved() const noexcept;*/

    const StringObject& getIterated() const noexcept;

    const char* getPosition() const noexcept;

protected:
    const StringObject& iterated;
    const char* position;
};