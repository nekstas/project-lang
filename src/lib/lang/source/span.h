#pragma once

#include <cstddef>

namespace lib::lang::source {

class Span {
public:
    Span(size_t offset, size_t length);

    size_t GetOffset() const {
        return offset_;
    }

    size_t GetLength() const {
        return length_;
    }

protected:
    size_t offset_;
    size_t length_;
};

}  // namespace lib::lang::source
