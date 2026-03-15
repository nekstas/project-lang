#pragma once

#include <exception>
#include <stdexcept>

#include "../utils/format_stream.h"

#define THROW(error_class, format_expr) \
    throw error_class(utils::FormatStream() << format_expr, __FILE__, __LINE__)
#define THROW_IF(condition, error_class, format_expr) \
    if (condition) {                                  \
        THROW(error_class, format_expr);              \
    }                                                 \
    (void)0

namespace errors {

class RuntimeError : public std::runtime_error {
public:
    RuntimeError(const std::string& message, const std::string& file, const size_t line);
};

class LogicError : public RuntimeError {
public:
    using RuntimeError::RuntimeError;
};

}  // namespace errors
