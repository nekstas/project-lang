#pragma once

#include <iostream>

#include "../../../lib/lang/backend/llir/generator.hpp"
#include "../../hlir/node.hpp"
#include "../../hlir/visitors/hlir_printer.h"
#include "../../hlir/visitors/llir_generator.h"

namespace lang::backend::llir {

template <lib::lang::ContextLike Context>
class Generator : public lib::lang::backend::llir::Generator<lang::hlir::Node, Context> {
private:
    using Super = lib::lang::backend::llir::Generator<lang::hlir::Node, Context>;

public:
    lib::lang::structure::Module Run(Super::HlirNodePtr ast, Context& ctx) const override {
#ifdef DEBUG_HLIR
        lang::hlir::visitors::HlirPrinter hlir_printer(2);
        std::cerr << "HLIR:\n";
        std::cerr << hlir_printer.ToString(ast.get());
        std::cerr << "\n";
#endif

        lang::hlir::visitors::LlirGenerator llir_generator(ctx);
        return llir_generator.Generate(ast.get());
    }
};

}  // namespace lang::backend::llir
