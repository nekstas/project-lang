#pragma once

#include <cassert>
#include <stdexcept>

// ReSharper disable once CppUnusedIncludeDirective
#include "../utils/format_stream.h"
#include "error_info.h"

#define VA_ARGS(...) , ##__VA_ARGS__
#define THROW(error_class, format_expr, ...)                                                    \
    throw error_class(::errors::ErrorInfo{::utils::FormatStream() << format_expr, #error_class, \
        __FILE__, __LINE__} VA_ARGS(__VA_ARGS__))
#define THROW_IF(condition, error_class, format_expr, ...) \
    do {                                                   \
        if (condition) {                                   \
            THROW(error_class, format_expr, __VA_ARGS__);  \
        }                                                  \
    } while (false)
#define UNREACHABLE                              \
    assert(false &&                              \
           "Code execution reached unreachable " \
           "line.")
#define ASSERT_NOT_NULL(condition) \
    THROW_IF((condition) == nullptr, ::errors::LogicError, "Unexpected null pointer.")
#define NOT_IMPLEMENTED_YET              \
    THROW(::errors::NotImplementedError, \
        "Function " << __PRETTY_FUNCTION__ << " is not implemented yet")

namespace errors {

class RuntimeError : public std::runtime_error {
public:
    explicit RuntimeError(const ErrorInfo& info);
};

class LogicError : public RuntimeError {
public:
    using RuntimeError::RuntimeError;
};

class NotImplementedError : public RuntimeError {
public:
    using RuntimeError::RuntimeError;
};

}  // namespace errors
