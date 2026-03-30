#include "source.h"

#include <sstream>

namespace lib::lang::source {

Source::Source(const std::string& name, const std::string& content)
    : name_(name), content_(content) {
    BuildIndex();
}

void Source::BuildIndex() {
    line_starts_.clear();
    line_starts_.push_back(0);
    for (size_t i = 0; i < Size(); ++i) {
        if (content_[i] == '\n') {
            line_starts_.push_back(i + 1);
        }
    }
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

}  // namespace lib::lang::source
