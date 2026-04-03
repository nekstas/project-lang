#pragma once

#include <filesystem>
#include <iostream>

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

    // ReSharper disable once CppNonExplicitConversionOperator
    operator std::filesystem::path() const {
        return GetOriginalPath();
    }

protected:
    std::filesystem::path original_path_;
    std::filesystem::path full_path_;
};

std::ostream& operator<<(std::ostream& out, const Path& path);

}  // namespace lib::lang::source
