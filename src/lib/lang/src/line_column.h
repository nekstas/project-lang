#pragma once

#include <ostream>

namespace lib::lang::src {

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

std::ostream& operator<<(std::ostream& out, const LineColumn& pos);

}  // namespace lib::lang::src
