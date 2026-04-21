#include "instruction_stringifier.h"

#include "../instruction.hpp"
#include "../instructions/load_int64.h"

namespace lib::lang::llir::visitors {

std::string InstructionStringifier::ToString(const Instruction* instr) {
    out_.str("");
    out_ << "~ ";
    if (instr) {
        instr->Accept(*this);
    } else {
        out_ << "nop";
    }
    return out_.str();
}

void InstructionStringifier::Visit(const instr::LoadInt64& instr) {
    out_ << "load_int64 " << instr.GetDesc() << " " << instr.GetValue();
}

}  // namespace lib::lang::llir::visitors
