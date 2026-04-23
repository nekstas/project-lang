#pragma once

#include "../../../../llir/visitor.h"
#include "../data/codegen_context.h"
#include "inner_context.h"

namespace lib::lang::backend::asm_::gas_x86_64::impl {

class LlirToAsm : public llir::Visitor {
public:
    LlirToAsm(CodegenContext& ctx, InnerContext& ic) : ctx_(ctx), ic_(ic) {}

    void Generate(const llir::Instruction* instr);

public:
    void Visit(const llir::instr::LoadInt64& instr) override;

private:
    CodegenContext& ctx_;
    InnerContext& ic_;
};

}  // namespace lib::lang::backend::asm_::gas_x86_64::impl