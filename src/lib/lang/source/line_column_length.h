#pragma once

#include <ostream>

namespace lib::lang::source {

class LineColumnLength {
public:
    LineColumnLength(size_t line, size_t column, size_t length);

    size_t GetLine() const {
        return line_;
    }

    size_t GetColumn() const {
        return column_;
    }

    size_t GetLength() const {
        return length_;
    }

protected:
    size_t line_;
    size_t column_;
    size_t length_;
};

std::ostream& operator<<(std::ostream& out, const LineColumnLength& pos);

}  // namespace lib::lang::source
