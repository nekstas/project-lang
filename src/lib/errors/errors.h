#pragma once

#include <cassert>
#include <stdexcept>

#include "../utils/format_stream.h"

#define VA_ARGS(...) , ##__VA_ARGS__
#define THROW(error_class, format_expr, ...)                            \
    throw error_class(::utils::FormatStream() << format_expr, __FILE__, \
                      __LINE__ VA_ARGS(__VA_ARGS__))
#define THROW_IF(condition, error_class, format_expr, ...) \
    if (condition) {                                       \
        THROW(error_class, format_expr, __VA_ARGS__);      \
    }                                                      \
    (void)0
#define UNREACHABLE assert(false && "Code execution reached unreachable line.")
#define ASSERT_NOT_NULL(condition) \
    THROW_IF((condition) == nullptr, ::errors::LogicError, "Unexpected null pointer.")

namespace errors {

class RuntimeError : public std::runtime_error {
public:
    RuntimeError(const std::string& message, const std::string& file, size_t line);
};

class LogicError : public RuntimeError {
public:
    using RuntimeError::RuntimeError;
};

}  // namespace errors
