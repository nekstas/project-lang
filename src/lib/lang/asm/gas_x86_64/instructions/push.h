#pragma once

#include "../enums/register.h"
#include "../instruction.h"
#include "../visitor.h"

namespace lib::lang::asm_::gas_x86_64::instr {

class Push : public Instruction {
public:
    explicit Push(e::Register reg) : reg_(reg) {
        // TODO: сделать проверки операндов на корректность
        TEMP_ASSERT(e::RegisterToSize(reg_) == 8);
    }

    e::Register GetReg() const {
        return reg_;
    }

    void Accept(Visitor& visitor) const override {
        visitor.Visit(*this);
    }

private:
    e::Register reg_;
};

}  // namespace lib::lang::asm_::gas_x86_64::instr
