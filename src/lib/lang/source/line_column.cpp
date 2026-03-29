#include "line_column.h"

namespace lib::lang::source {

LineColumn::LineColumn(size_t line, size_t column) : line_(line), column_(column) {}

}  // namespace lib::lang::source