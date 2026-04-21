#pragma once

#include <sstream>

#include "../../fwd.h"
#include "../../hlir/node.hpp"
#include "../visitor.h"

namespace lang::ast::visitors {

class HlirGenerator : public Visitor {
public:
    std::unique_ptr<hlir::Node> Generate(const Node* ast);

public:
    void Visit(const expr::lit::IntLiteral& lit) override;

private:
    std::unique_ptr<hlir::Node> result_;
};

}  // namespace lang::ast::visitors
