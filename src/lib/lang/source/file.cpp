#include "file.h"

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

}  // namespace lib::lang::source