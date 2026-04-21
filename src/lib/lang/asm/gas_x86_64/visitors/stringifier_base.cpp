#include "stringifier_base.h"

#include "../directives/intel_syntax.h"

namespace lib::lang::asm_::gas_x86_64 {

std::string StringifierBase::ToString(const Unit<Line>& unit) {
    std::stringstream result_;
    dir::IntelSyntax begin{e::IntelSyntax::NO_PREFIX};
    result_ << ToString(&begin) << "\n";
    for (const auto& line : unit.GetLines()) {
        result_ << ToString(line.get()) << "\n";
    }
    return result_.str();
}

void StringifierBase::Visit(const dir::IntelSyntax& dir) {
    out_ << ".intel_syntax " << dir.GetIntelSyntax();
}

}  // namespace lib::lang::asm_::gas_x86_64
