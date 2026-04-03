#include "source.h"

#include <sstream>

namespace lib::lang::src {

Source::Source(const std::string& name, const std::string& content)
    : name_(name), content_(content), index_(content_) {}

std::string Source::GetLine(size_t line_number) const {
    return index_.GetLine(line_number);
}

std::ostream& operator<<(std::ostream& out, const Source& source) {
    std::stringstream first_line_out;
    first_line_out << source.GetTitle();
    std::string first_line = first_line_out.str();

    out << first_line << "\n";
    out << std::string(first_line.size(), '-') << "\n";
    out << source.GetContent() << "\n";
    return out;
}

}  // namespace lib::lang::src
