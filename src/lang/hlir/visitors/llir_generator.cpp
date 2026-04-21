#include "llir_generator.h"

#include "../../../lib/lang/llir/instructions/load_int64.h"
#include "../../../lib/lang/symbols/scopes/function_scope.h"
#include "../../hlir/expr/lit/int_literal.h"

namespace lang::hlir::visitors {

lib::lang::llir::InstructionSequence LlirGenerator::Generate(const Node* ast) {
    result_ = {};
    last_temp_var_ = nullptr;
    if (ast) {
        ast->Accept(*this);
    }
    return std::move(result_);
}

void LlirGenerator::Visit(const expr::lit::IntLiteral& lit) {
    auto scope = ctx_.symbols.AddScope<lib::lang::symbols::FunctionScope>();
    last_temp_var_ = scope->CreateTempVar();
    result_.AddInstruction<lib::lang::llir::instr::LoadInt64>(last_temp_var_, lit.GetValue());
}

}  // namespace lang::hlir::visitors
