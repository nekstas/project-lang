#pragma once

#include "../../render/span.h"
#include "../../source/span.h"

namespace lib::lang::diag {

class SourceDiag : public Diag {
public:
    SourceDiag(Severity severity, const source::Span& span) : Diag(severity), span_(span) {}

    virtual std::string GetSubMessage() const = 0;

    std::string GetMessage(const render::Context& ctx) const override {
        std::stringstream out;
        out << render::Span{GetSubMessage(), GetSpan(), ctx};
        return out.str();
    }

protected:
    source::Span GetSpan() const {
        return span_;
    }

private:
    source::Span span_;
};

class UnexpectedSymbolError : public SourceDiag {
public:
    explicit UnexpectedSymbolError(const source::Span& span) : SourceDiag(Severity::ERROR, span) {}

    std::string GetSubMessage() const override {
        return "Unexpected symbol.";
    }
};

}  // namespace lib::lang::diag
