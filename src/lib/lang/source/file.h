#pragma once

#include <cstddef>
#include <string>
#include <vector>

#include "path.h"

namespace lib::lang::source {

class File {
public:
    File(const Path& path, const std::string& content);

    const Path& GetPath() const {
        return path_;
    }

    size_t Size() const {
        return content_.size();
    }

private:
    void BuildIndex();

protected:
    Path path_;
    std::string content_;
    std::vector<size_t> line_starts_;
};

}  // namespace lib::lang::source
