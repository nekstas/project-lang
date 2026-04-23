#include <iostream>

#include "lang/backend/backend.h"
#include "lang/frontend/frontend.h"
#include "lib/flow/static_pipeline.hpp"
#include "lib/lang/asm/gas_x86_64/visitors/intel_stringifier.h"
#include "lib/lang/backend/asm/gas_x86_64/data/codegen_context.h"
#include "lib/lang/context/base_context.h"

struct Context : lib::lang::backend::asm_::gas_x86_64::CodegenContext {};

int main() {
    auto pipeline = lib::flow::MakeStaticNamedPipeline<Context>("LangPipeline",
        lang::frontend::ReadFile<Context>(), lang::frontend::Lexer<Context>(),
        lang::frontend::TokensFilter<Context>(), lang::frontend::Parser<Context>(),
        lang::backend::HlirGenerator<Context>(), lang::backend::LlirGenerator<Context>(),
        lang::backend::AsmGenerator<Context>());

    std::cout << "Hello, project-lang!\n";
    std::cout << pipeline.Name() << "\n\n";

    Context ctx;
    try {
        auto result = pipeline.Run("../../test.lang", ctx);
        lib::lang::asm_::gas_x86_64::IntelStringifier stringifier(4);
        std::cerr << "ASM:\n";
        std::cerr << stringifier.ToString(std::move(result)) << "\n";
    } catch (const lib::flow::StopPipeline& stop_pipeline) {
        std::cerr << "Pipeline stopped: " << stop_pipeline.GetLocation() << "\n";
    }
    std::cerr << ctx.diag.GetDiagnosticsString(ctx);
}
