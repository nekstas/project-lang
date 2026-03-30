#include <iostream>

#include "lang/frontend/frontend.h"
#include "lang/frontend/tokens_filter/tokens_filter.hpp"
#include "lib/flow/static_pipeline.hpp"
#include "lib/lang/context/base_context.h"
#include "lib/lang/frontend/file_reader/file_reader.hpp"

struct Context : lib::lang::BaseContext {};

int main() {
    auto pipeline = lib::flow::MakeStaticNamedPipeline<Context>("LangPipeline",
        lang::frontend::ReadFile<Context>{}, lang::frontend::Lexer<Context>{},
        lang::frontend::TokensFilter<Context>{});

    std::cout << "Hello, project-lang!\n";
    std::cout << pipeline.Name() << "\n";

    Context ctx;
    try {
        auto result = pipeline.Run("../../example.lang", ctx);
        for (const auto token : result) {
            std::cout << token << "\n";
        }
        std::cout << "End.\n";
    } catch (const lib::flow::StopPipeline& stop_pipeline) {
        std::cerr << "Pipeline stopped: " << stop_pipeline.GetLocation() << "\n";
    }
    std::cerr << ctx.diag.GetDiagnosticsString(ctx);
}
