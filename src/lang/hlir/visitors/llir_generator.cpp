#include "llir_generator.h"

#include "../../../lib/lang/llir/instructions/load_int64.h"
#include "../../../lib/lang/symbols/scopes/function_scope.h"
#include "../../../lib/lang/symbols/scopes/global_scope.h"
#include "../../hlir/expr/lit/int_literal.h"

namespace lang::hlir::visitors {

lib::lang::structure::Module LlirGenerator::Generate(const Node* ast) {
    result_ = {};

    // TODO: подвинуть в более подходящее место
    sequence_ = {};
    auto scope = ctx_.symbols.AddScope<lib::lang::symbols::GlobalScope>();
    auto desc = scope->CreateFunction("main", ctx_);
    current_scope_ = desc->GetFunctionScope();

    if (ast) {
        ast->Accept(*this);
    }

    // TODO: подвинуть в более подходящее место
    lib::lang::structure::Function function(desc, std::move(sequence_));
    result_.AddFunction(std::move(function));

    return std::move(result_);
}

void LlirGenerator::Visit(const expr::lit::IntLiteral& lit) {
    auto scope = CastScope<lib::lang::symbols::FunctionScope>(current_scope_);
    TEMP_ASSERT(scope);
    last_temp_var_ = scope->CreateTempVar();
    sequence_.AddInstruction<lib::lang::llir::instr::LoadInt64>(last_temp_var_, lit.GetValue());
}

}  // namespace lang::hlir::visitors
