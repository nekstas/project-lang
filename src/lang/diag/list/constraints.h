#pragma once

#include <sstream>
#include <string>
#include <utility>

#include "../../../lib/lang/diag/diag.h"

namespace lang::diag {

class CommandLineFatal : public lib::lang::diag::Diag {
public:
    explicit CommandLineFatal(std::string message)
        : Diag(lib::lang::diag::Severity::FATAL), message_(std::move(message)) {}

    std::string GetMessage(const lib::lang::render::Context&) const override {
        std::stringstream out;
        out << "Command line error: " << message_ << "\n";
        return out.str();
    }

private:
    std::string message_;
};

class ConstraintViolationFatal : public lib::lang::diag::Diag {
public:
    explicit ConstraintViolationFatal(std::string message)
        : Diag(lib::lang::diag::Severity::FATAL), message_(std::move(message)) {}

    std::string GetMessage(const lib::lang::render::Context&) const override {
        std::stringstream out;
        out << "Constraint violation: " << message_ << "\n";
        return out.str();
    }

private:
    std::string message_;
};

}  // namespace lang::diag
