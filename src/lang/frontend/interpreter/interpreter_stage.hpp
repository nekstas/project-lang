#pragma once

#include <exception>
#include <iostream>
#include <istream>
#include <memory>
#include <ostream>
#include <string>

#include "../../../lib/flow/typed_stage.hpp"
#include "../../../lib/lang/context/base_context.h"
#include "../../../lib/lang/macros.h"
#include "../../ast/node.hpp"
#include "../../ast/visitors/interpreter.h"
#include "../../diag/list/interpreter.h"

namespace lang::frontend {

template <lib::lang::ContextLike Context>
class InterpreterStage
    : public lib::flow::TypedStage<InterpreterStage<Context>, Context, std::shared_ptr<ast::Node>,
          std::shared_ptr<ast::Node>> {
public:
    explicit InterpreterStage(std::istream& in = std::cin, std::ostream& out = std::cout)
        : in_(in), out_(out) {}

    std::shared_ptr<ast::Node> Run(std::shared_ptr<ast::Node> node, Context& ctx) const {
        try {
            ast::visitors::Interpreter interpreter{in_, out_};
            interpreter.Execute(node.get());
        } catch (const ast::visitors::InterpreterRuntimeError& err) {
            DIAG_REPORT(ctx, lang::diag::InterpreterRuntimeFatal, err.what());
        } catch (const std::exception& err) {
            DIAG_REPORT(ctx, lang::diag::InterpreterRuntimeFatal, err.what());
        }
        return node;
    }

    std::string Name() const override {
        return "Interpreter";
    }

private:
    std::istream& in_;
    std::ostream& out_;
};

}  // namespace lang::frontend
