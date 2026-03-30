#pragma once

#include <cstddef>

namespace lib::lang::render {

class LineSpan {
public:
    LineSpan(size_t first_column, size_t length);

    size_t GetFirstColumn() const {
        return first_column_;
    }

    size_t GetLength() const {
        return length_;
    }

private:
    size_t first_column_;
    size_t length_;
};

}  // namespace lib::lang::render
