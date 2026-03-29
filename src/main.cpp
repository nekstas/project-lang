#include <iostream>

#include "lib/flow/static_pipeline.hpp"
#include "lib/lang/context/base_context.h"
#include "lib/lang/frontend/read_file/read_file.hpp"

struct Context : lib::lang::BaseContext {};

int main() {
    auto pipeline = lib::flow::MakeStaticNamedPipeline<Context>(
        "LangPipeline", lib::lang::frontend::ReadFileStage<Context>{});

    std::cout << "Hello, project-lang!\n";
    std::cout << pipeline.Name() << "\n";

    Context ctx;
    try {
        auto result = pipeline.Run("../../example.lang", ctx);
        std::cout << result;
    } catch (const lib::flow::StopPipeline& stop_pipeline) {
        std::cerr << "Pipeline stopped: " << stop_pipeline.GetLocation() << "\n";
    }
    std::cerr << ctx.diag.GetDiagnosticsString();
}
