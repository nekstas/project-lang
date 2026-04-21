#pragma once

#include "../../../lib/lang/context/base_context.h"
#include "../../../lib/lang/llir/instruction_sequence.h"
#include "../../fwd.h"
#include "../visitor.h"

namespace lang::hlir::visitors {

class LlirGenerator : public Visitor {
public:
    explicit LlirGenerator(lib::lang::BaseContext& ctx) : ctx_(ctx), last_temp_var_() {}

    lib::lang::llir::InstructionSequence Generate(const Node* ast);

public:
    void Visit(const expr::lit::IntLiteral& lit) override;

private:
    lib::lang::BaseContext& ctx_;
    lib::lang::llir::InstructionSequence result_;
    lib::lang::symbols::TempVariableDescriptor* last_temp_var_;
};

}  // namespace lang::hlir::visitors
