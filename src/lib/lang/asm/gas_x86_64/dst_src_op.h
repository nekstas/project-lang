#pragma once

#include "instruction.h"
#include "operand.h"
#include "visitor.h"

namespace lib::lang::asm_::gas_x86_64 {

class OpDstSrc : public Instruction {
public:
    OpDstSrc(Operand dst, Operand src) : dst_(std::move(dst)), src_(std::move(src)) {}

    virtual std::string GetOp() const = 0;

    Operand GetSrc() const {
        return src_;
    }

    Operand GetDst() const {
        return dst_;
    }

    void Accept(Visitor& visitor) const override {
        visitor.Visit(*this);
    }

private:
    Operand dst_;
    Operand src_;
};

}  // namespace lib::lang::asm_::gas_x86_64
