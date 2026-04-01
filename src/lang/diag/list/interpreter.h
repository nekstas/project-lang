#pragma once

#include <sstream>
#include <string>
#include <utility>

#include "../../../lib/lang/diag/diag.h"

namespace lang::diag {

class InterpreterRuntimeFatal : public lib::lang::diag::Diag {
public:
    explicit InterpreterRuntimeFatal(std::string message)
        : Diag(lib::lang::diag::Severity::FATAL), message_(std::move(message)) {}

    std::string GetMessage(const lib::lang::render::Context&) const override {
        std::stringstream out;
        out << "Interpreter runtime error: " << message_ << "\n";
        return out.str();
    }

private:
    std::string message_;
};

}  // namespace lang::diag
