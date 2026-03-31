#pragma once

#include "../fwd.h"

namespace lang::ast {

class Visitor {
public:
    virtual ~Visitor() {}

    virtual void Visit(const expr::lit::IntLiteral& expr) = 0;
    virtual void Visit(const expr::BinaryExpression& expr) = 0;
};

}  // namespace lang::ast
