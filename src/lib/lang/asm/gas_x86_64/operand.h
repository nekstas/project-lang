#pragma once

#include <cstdint>
#include <iostream>
#include <variant>

#include "enums/register.h"
#include "memory.h"

namespace lib::lang::asm_::gas_x86_64 {

class Operand;

namespace op {

Operand Reg(e::Register reg);
Operand Imm32(int32_t value);
Operand Imm64(int64_t value);
Operand RbpRel(int32_t diff);

}  // namespace op

// TODO: сделать проверки корректности операнда
// TODO: подумать, как лучше его реализовать всё же
class Operand {
    friend Operand op::Reg(e::Register reg);
    friend Operand op::Imm32(int32_t value);
    friend Operand op::Imm64(int64_t value);
    friend Operand op::RbpRel(int32_t diff);

private:
    using InnerOperand = std::variant<e::Register, int32_t, int64_t, mem::StackRbpRelativeAddress>;

private:
    explicit Operand(InnerOperand value) : value_(value) {}

public:
    const InnerOperand& GetInner() const {
        return value_;
    }

private:
    InnerOperand value_;
};

std::ostream& operator<<(std::ostream& out, const Operand& operand);

}  // namespace lib::lang::asm_::gas_x86_64
