#include <iostream>

#include "lang/backend/backend.h"
#include "lang/frontend/frontend.h"
#include "lang/hlir/visitors/hlir_printer.h"
#include "lib/flow/static_pipeline.hpp"
#include "lib/lang/context/base_context.h"

struct Context : lib::lang::BaseContext {};

int main() {
    auto pipeline = lib::flow::MakeStaticNamedPipeline<Context>("LangPipeline",
        lang::frontend::ReadFile<Context>{}, lang::frontend::Lexer<Context>{},
        lang::frontend::TokensFilter<Context>{}, lang::frontend::Parser<Context>{},
        lang::backend::HlirGenerator<Context>{});

    std::cout << "Hello, project-lang!\n";
    std::cout << pipeline.Name() << "\n";

    Context ctx;
    try {
        auto result = pipeline.Run("../../test.lang", ctx);
        // for (auto token : result) {
        // std::cout << token << "\n";
        // }
        lang::hlir::visitors::HlirPrinter hlir_printer(2);
        std::cout << "HLIR:\n";
        std::cout << hlir_printer.ToString(result.get());
    } catch (const lib::flow::StopPipeline& stop_pipeline) {
        std::cerr << "Pipeline stopped: " << stop_pipeline.GetLocation() << "\n";
    }
    std::cerr << ctx.diag.GetDiagnosticsString(ctx);
}
