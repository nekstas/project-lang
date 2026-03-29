#pragma once

#include <cstddef>

namespace lib::lang::source {

class LineColumn {
public:
    LineColumn(size_t line, size_t column);

    size_t GetLine() const {
        return line_;
    }

    size_t GetColumn() const {
        return column_;
    }

protected:
    size_t line_;
    size_t column_;
};

}  // namespace lib::lang::source
