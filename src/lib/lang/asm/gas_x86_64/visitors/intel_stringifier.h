#pragma once

#include <string>

#include "stringifier_base.h"

namespace lib::lang::asm_::gas_x86_64 {

class IntelStringifier : public StringifierBase {
public:
    using StringifierBase::StringifierBase;

    using StringifierBase::ToString;
    std::string ToString(const gas_x86_64::Line* line) override;

public:
    void Visit(const OpDstSrc& instr) override;
    void Visit(const instr::Push& instr) override;
    void Visit(const instr::Pop& instr) override;
    void Visit(const instr::Ret& instr) override;
};

}  // namespace lib::lang::asm_::gas_x86_64