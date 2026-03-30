#include "errors.h"

#include "../utils/format_stream.h"

namespace errors {

RuntimeError::RuntimeError(const ErrorInfo& info)
    : std::runtime_error(::utils::FormatStream()
                         << "An exception " << info.error_cls_name << " has occurred.\n"
                         << "File " << info.file << ":" << info.line << ".\n"
                         << info.message) {}

}  // namespace errors
