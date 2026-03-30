#include "line_column_length.h"

namespace lib::lang::source {

LineColumnLength::LineColumnLength(size_t line, size_t column, size_t length)
    : line_(line), column_(column), length_(length) {}

std::ostream& operator<<(std::ostream& out, const LineColumnLength& pos) {
    out << pos.GetLine() << ":" << pos.GetColumn();
    out << " .. ";
    out << pos.GetLine() << ":" << pos.GetColumn() + pos.GetLength();
    return out;
}

}  // namespace lib::lang::source