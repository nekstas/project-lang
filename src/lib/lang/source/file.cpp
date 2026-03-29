#include "file.h"

#include <sstream>

namespace lib::lang::source {

File::File(const Path& path, const std::string& content) : path_(path), content_(content) {
    BuildIndex();
}

void File::BuildIndex() {
    line_starts_.clear();
    line_starts_.push_back(0);
    for (size_t i = 0; i < Size(); ++i) {
        if (content_[i] == '\n') {
            line_starts_.push_back(i + 1);
        }
    }
}

std::ostream& operator<<(std::ostream& out, const File& file) {
    std::stringstream first_line_out;
    first_line_out << "File " << file.GetPath();
    std::string first_line = first_line_out.str();

    out << first_line << "\n";
    out << std::string(first_line.size(), '-') << "\n";
    out << file.GetContent() << "\n";
    return out;
}

}  // namespace lib::lang::source