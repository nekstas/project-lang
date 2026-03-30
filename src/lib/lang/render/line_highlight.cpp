#include "line_highlight.h"

#include <iomanip>

#include "../../utils/utils.h"

namespace lib::lang::render {

LineHighlight::LineHighlight(const std::string& line_content, size_t line_number,
    size_t align_length, const LineSpan& line_span)
    : line_content_(line_content)
    , line_number_(line_number)
    , align_length_(align_length)
    , line_span_(line_span) {
    ::utils::StripNewline(line_content_);
    THROW_IF(line_content_.contains('\n'), ::errors::LogicError,
        "Line should contain no new line symbols.");
}

std::ostream& operator<<(std::ostream& out, const LineHighlight& item) {
    std::stringstream prefix_out;
    prefix_out << " ";
    prefix_out << std::right << std::setfill(' ');
    prefix_out << std::setw(item.align_length_) << item.line_number_;
    prefix_out << " | ";
    std::string prefix = prefix_out.str();

    size_t first_column = item.line_span_.GetFirstColumn();
    size_t length = item.line_span_.GetLength();

    out << prefix << item.line_content_ << "\n";
    out << std::string(prefix.size(), ' ');
    out << std::string(first_column - 1, ' ');

    out << std::string(length, '^') << "\n";
    return out;
}

}  // namespace lib::lang::render
