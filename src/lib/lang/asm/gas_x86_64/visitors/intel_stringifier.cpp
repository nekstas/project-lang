#include "intel_stringifier.h"

#include "../instructions/mov.h"
#include "../instructions/pop.h"
#include "../instructions/push.h"
#include "../line.h"

namespace lib::lang::asm_::gas_x86_64 {

std::string IntelStringifier::ToString(const gas_x86_64::Line* line) {
    out_.str("");
    if (line) {
        line->Accept(*this);
    }
    return out_.str();
}

void IntelStringifier::Visit(const OpDstSrc& instr) {
    out_ << instr.GetOp() << " " << instr.GetDst() << ", " << instr.GetSrc();
}

void IntelStringifier::Visit(const instr::Push& instr) {
    out_ << "push " << instr.GetReg();
}

void IntelStringifier::Visit(const instr::Pop& instr) {
    out_ << "pop " << instr.GetReg();
}

void IntelStringifier::Visit(const instr::Ret& instr) {
    out_ << "ret";
}

}  // namespace lib::lang::asm_::gas_x86_64
