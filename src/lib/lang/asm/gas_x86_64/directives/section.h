#pragma once

#include "../directive.h"
#include "../enums/section.h"
#include "../visitor.h"

namespace lib::lang::asm_::gas_x86_64::dir {

class Section : public Directive {
public:
    explicit Section(e::Section section) : section_(section) {}

    e::Section GetSection() const {
        return section_;
    }

    void Accept(Visitor& visitor) const override {
        visitor.Visit(*this);
    }

private:
    e::Section section_;
};

}  // namespace lib::lang::asm_::gas_x86_64::dir
