#pragma once

#include "../errors/errors.h"
#include "parser/error_state.h"

namespace lang::regex::errors {

class ParserError : public ::errors::RuntimeError {
public:
    ParserError(const std::string& message, const std::string& error_cls_name,
                const std::string& file, size_t line, const parser::ErrorState& error_state);

    static std::string ConstructMessageFromErrorState(const parser::ErrorState& error_state);

private:
    parser::ErrorState error_state_;
};

class DfaBuilderError : public ::errors::RuntimeError {
public:
    using RuntimeError::RuntimeError;
};

}  // namespace lang::regex::errors
