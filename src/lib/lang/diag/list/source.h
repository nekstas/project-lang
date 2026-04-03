#pragma once

#include "../../render/span.h"
#include "../../src/span.h"

namespace lib::lang::diag {

class SourceDiag : public Diag {
public:
    SourceDiag(Severity severity, const src::Span& span) : Diag(severity), span_(span) {}

    virtual std::string GetSubMessage() const = 0;

    std::string GetMessage(const render::Context& ctx) const override {
        std::stringstream out;
        out << render::Span{GetSubMessage(), GetSpan(), ctx};
        return out.str();
    }

protected:
    src::Span GetSpan() const {
        return span_;
    }

private:
    src::Span span_;
};

class UnexpectedSymbolError : public SourceDiag {
public:
    explicit UnexpectedSymbolError(const src::Span& span) : SourceDiag(Severity::ERROR, span) {}

    std::string GetSubMessage() const override {
        return "Unexpected symbol.";
    }
};

}  // namespace lib::lang::diag
