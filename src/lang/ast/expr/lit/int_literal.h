#pragma once

#include "../../visitor.h"
#include "../literal.h"

namespace lang::ast::expr::lit {

class IntLiteral : public Literal {
public:
    using Literal::Literal;

    void Accept(Visitor& visitor) const override {
        visitor.Visit(*this);
    }
};

}  // namespace lang::ast::expr::lit
