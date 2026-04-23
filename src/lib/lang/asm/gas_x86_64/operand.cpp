#include "operand.h"

namespace lib::lang::asm_::gas_x86_64 {

Operand op::Reg(e::Register reg) {
    return Operand(reg);
}

Operand op::Imm32(int32_t value) {
    return Operand(value);
}

Operand op::Imm64(int64_t value) {
    return Operand(value);
}

Operand op::RbpRel(int32_t diff) {
    return Operand(mem::StackRbpRelativeAddress(diff));
}

std::ostream& operator<<(std::ostream& out, const Operand& operand) {
    auto out_func = [&out](auto&& value) { out << value; };
    std::visit(out_func, operand.GetInner());
    return out;
}

}  // namespace lib::lang::asm_::gas_x86_64
