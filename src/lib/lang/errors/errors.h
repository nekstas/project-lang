#pragma once

#include "../../errors/errors.h"

namespace lib::lang::errors {

class LangPipelineError : public ::errors::RuntimeError {
public:
    explicit LangPipelineError(const ::errors::ErrorInfo& info) : RuntimeError(info) {}
};

struct InvalidEncodingInfo {
    std::string prefix;
    size_t line_number;
    size_t length;
};

class InvalidEncodingError : public LangPipelineError {
public:
    explicit InvalidEncodingError(
        const ::errors::ErrorInfo& info, const InvalidEncodingInfo& err_info)
        : LangPipelineError(info), err_info_(err_info) {}

    const InvalidEncodingInfo& GetErrInfo() const {
        return err_info_;
    }

private:
    std::string prefix_;
    InvalidEncodingInfo err_info_;
};

}  // namespace lib::lang::errors
