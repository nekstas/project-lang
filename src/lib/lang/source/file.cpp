#include "file.h"

namespace lib::lang::source {

File::File(const Path& path, const std::string& content)
    : Source(path.GetFullPath().string(), content), path_(path) {}

std::string File::GetTitle() const {
    return ::utils::FormatStream{} << "File " << std::quoted(GetName());
}

}  // namespace lib::lang::source