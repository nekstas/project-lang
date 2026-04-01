#pragma once

#include <iomanip>
#include <sstream>
#include <string>
#include <utility>

#include "../../../lib/lang/diag/list/source.h"

namespace lang::diag {

class ParserExpectedTokenFatal : public lib::lang::diag::SourceDiag {
public:
    ParserExpectedTokenFatal(const lib::lang::source::Span& span, std::string expected,
        std::string got)
        : SourceDiag(lib::lang::diag::Severity::FATAL, span)
        , expected_(std::move(expected))
        , got_(std::move(got)) {}

    std::string GetSubMessage() const override {
        std::stringstream out;
        out << "Syntax error: expected " << expected_ << ", got " << got_ << ".";
        return out.str();
    }

private:
    std::string expected_;
    std::string got_;
};

class ParserUnsupportedTypeFatal : public lib::lang::diag::SourceDiag {
public:
    ParserUnsupportedTypeFatal(const lib::lang::source::Span& span, std::string type_name)
        : SourceDiag(lib::lang::diag::Severity::FATAL, span), type_name_(std::move(type_name)) {}

    std::string GetSubMessage() const override {
        std::stringstream out;
        out << "Unsupported type " << std::quoted(type_name_)
            << ". Only \"Int\" is supported now.";
        return out.str();
    }

private:
    std::string type_name_;
};

}  // namespace lang::diag
