#include "path.h"

#include <iomanip>
#include <utility>

lib::lang::src::Path::Path(const std::filesystem::path& original_path)
    : original_path_(original_path) {
    full_path_ = std::filesystem::absolute(original_path);
}

std::ostream& lib::lang::src::operator<<(std::ostream& out, const Path& path) {
    return out << std::quoted(path.GetFullPath().string());
}