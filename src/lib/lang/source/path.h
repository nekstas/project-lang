#pragma once

#include <filesystem>

namespace lib::lang::source {

class Path {
public:
    explicit Path(const std::filesystem::path& original_path);

    const std::filesystem::path& GetOriginalPath() const {
        return original_path_;
    }

    const std::filesystem::path& GetFullPath() const {
        return full_path_;
    }

protected:
    std::filesystem::path original_path_;
    std::filesystem::path full_path_;
};

}  // namespace lib::lang::source
