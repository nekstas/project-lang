#pragma once

#include "../../errors/errors.h"
#include "../parser/error_state.h"

namespace lib::regex::errors {

class ParserError : public ::errors::RuntimeError {
public:
    ParserError(const ::errors::ErrorInfo& info, const parser::ErrorState& error_state);

    static std::string ConstructMessageFromErrorState(const parser::ErrorState& error_state);

private:
    parser::ErrorState error_state_;
};

class DfaBuilderError : public ::errors::RuntimeError {
public:
    using RuntimeError::RuntimeError;
};

}  // namespace lib::regex::errors
