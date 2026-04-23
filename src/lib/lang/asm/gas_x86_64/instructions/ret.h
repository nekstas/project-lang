#pragma once

#include "../enums/register.h"
#include "../instruction.h"
#include "../visitor.h"

namespace lib::lang::asm_::gas_x86_64::instr {

class Ret : public Instruction {
public:
    explicit Ret() = default;

    void Accept(Visitor& visitor) const override {
        visitor.Visit(*this);
    }
};

}  // namespace lib::lang::asm_::gas_x86_64::instr
