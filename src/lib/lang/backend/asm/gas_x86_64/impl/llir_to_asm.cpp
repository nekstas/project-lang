#include "llir_to_asm.h"

#include "../../../../llir/instruction.hpp"
#include "../../../../llir/instructions/load_int64.h"

namespace lib::lang::backend::asm_::gas_x86_64::impl {

void LlirToAsm::Generate(const llir::Instruction* instr) {
    if (instr) {
        instr->Accept(*this);
    }
}

void LlirToAsm::Visit(const llir::instr::LoadInt64& instr) {}

}  // namespace lib::lang::backend::asm_::gas_x86_64::impl
