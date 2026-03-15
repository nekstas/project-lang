#include "errors.h"

namespace errors {

RuntimeError::RuntimeError(const std::string& message, const std::string& file, const size_t line)
    : std::runtime_error(utils::FormatStream() << "An exception has occurred.\n"
                                               << "File " << file << ":" << line << ".\n"
                                               << message) {}

}  // namespace errors
