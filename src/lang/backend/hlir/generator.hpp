#pragma once

#include "../../../lib/lang/backend/hlir/generator.hpp"
#include "../../ast/node.hpp"
#include "../../ast/visitors/hlir_generator.h"
#include "../../hlir/node.hpp"

namespace lang::backend::hlir {

template <lib::lang::ContextLike Context>
class Generator : public lib::lang::backend::hlir::Generator<ast::Node, lang::hlir::Node, Context> {
private:
    using Super = lib::lang::backend::hlir::Generator<ast::Node, lang::hlir::Node, Context>;

public:
    Super::HlirNodePtr Run(Super::AstNodePtr ast, Context& ctx) const override {
        ast::visitors::HlirGenerator hlir_generator;
        return hlir_generator.Generate(ast.get());
    }
};

}  // namespace lang::backend::hlir
