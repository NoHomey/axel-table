#include "StringCell.h"
#include <utility>

StringCell::StringCell(FixedSizeString&& string) noexcept
: value{std::move(string)} {}

StringCell::operator Number() const noexcept {
    return {};
}