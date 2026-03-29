#include "path.h"

lib::lang::source::Path::Path(const std::filesystem::path& original_path)
    : original_path_(original_path) {
    full_path_ = std::filesystem::absolute(original_path);
}