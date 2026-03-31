#pragma once

#include <sstream>

#include "../../../lib/utils/indentable.h"
#include "../../fwd.h"
#include "../visitor.h"

namespace lang::ast::visitors {

class AstPrinter : public ::utils::Indentable, public Visitor {
public:
    using Indentable::Indentable;

    std::string ToString(const Node* node);

public:
    void Visit(const expr::lit::IntLiteral& lit) override;
    void Visit(const expr::BinaryExpression& expr) override;

private:
    std::stringstream out_;
};

}  // namespace lang::ast::visitors
