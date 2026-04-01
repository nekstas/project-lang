#include <iostream>
#include <string>
#include <vector>

#include "lang/ast/visitors/ast_printer.h"
#include "lang/context/lang_context.h"
#include "lang/frontend/frontend.h"
#include "lang/frontend/parser/recursive_descent_parser.hpp"
#include "lang/frontend/tokens_filter/tokens_filter.hpp"
#include "lib/flow/static_pipeline.hpp"
#include "lib/lang/frontend/file_reader/file_reader.hpp"

int main(int argc, char* argv[]) {
    auto pipeline = lib::flow::MakeStaticNamedPipeline<lang::LangContext>("LangPipeline",
        lang::frontend::ParseCommandLineArgs<lang::LangContext>{},
        lang::frontend::ReadFile<lang::LangContext>{}, lang::frontend::Lexer<lang::LangContext>{},
        lang::frontend::TokensFilter<lang::LangContext>{},
        lang::frontend::RecursiveDescentParser<lang::LangContext>{},
        lang::frontend::StaticConstraints<lang::LangContext>{},
        lang::frontend::Interpreter<lang::LangContext>{});

    std::vector<std::string> args;
    args.reserve(static_cast<size_t>(argc > 0 ? argc - 1 : 0));
    for (int i = 1; i < argc; ++i) {
        args.emplace_back(argv[i]);
    }

    lang::LangContext ctx;
    try {
        pipeline.Run(args, ctx);
    } catch (const lib::flow::StopPipeline& stop_pipeline) {
        std::cerr << "Pipeline stopped: " << stop_pipeline.GetLocation() << "\n";
    }
    std::cerr << ctx.diag.GetDiagnosticsString(ctx);
}
