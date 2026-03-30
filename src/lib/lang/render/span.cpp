#include "span.h"

#include "line_highlight.h"

namespace lib::lang::render {

std::ostream& operator<<(std::ostream& out, const Span& item) {
    const auto& span = item.span_;
    const auto& source = item.ctx_.src.GetSource(span.GetDesc());
    auto line_column_length = source.GetIndex().GetFirstLineForSpan(span);

    size_t line_number = line_column_length.GetLine();
    size_t column = line_column_length.GetColumn();
    size_t length = line_column_length.GetLength();
    size_t align_length = item.ctx_.src.GetStats().GetMaxLineNumberLen();

    out << source.GetName();
    out << ":" << line_number;
    out << ":" << column;
    out << ": " << item.message_ << "\n";

    LineSpan line_span{column, length};
    out << LineHighlight{source.GetLine(line_number), line_number, align_length, line_span};
    return out;
}

}  // namespace lib::lang::render
