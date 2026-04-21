#pragma once

#include "../fwd.h"

namespace lang::hlir {

class Visitor {
public:
    virtual ~Visitor() {}

    virtual void Visit(const expr::lit::IntLiteral& expr) = 0;
};

}  // namespace lang::hlir
