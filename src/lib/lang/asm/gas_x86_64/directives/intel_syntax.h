#pragma once

#include "../directive.h"
#include "../enums/intel_syntax.h"
#include "../fwd.h"

namespace lib::lang::asm_::gas_x86_64::dir {

class IntelSyntax : public Directive {
public:
    explicit IntelSyntax(e::IntelSyntax intel_syntax) : intel_syntax_(intel_syntax) {}

    e::IntelSyntax GetIntelSyntax() const {
        return intel_syntax_;
    }

    void Accept(Visitor& visitor) const override {
        visitor.Visit(*this);
    }

private:
    e::IntelSyntax intel_syntax_;
};

}  // namespace lib::lang::asm_::gas_x86_64::dir
