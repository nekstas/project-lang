#include "line_column.h"

namespace lib::lang::source {

LineColumn::LineColumn(size_t line, size_t column) : line_(line), column_(column) {}

std::ostream& operator<<(std::ostream& out, const LineColumn& pos) {
    return out << pos.GetLine() << ":" << pos.GetColumn();
}

}  // namespace lib::lang::source