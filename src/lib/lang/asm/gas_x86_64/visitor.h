#pragma once

#include "fwd.h"

namespace lib::lang::asm_::gas_x86_64 {

class Visitor {
public:
    virtual ~Visitor() {}

    virtual void Visit(const dir::IntelSyntax& dir) = 0;
};

}  // namespace lib::lang::asm_::gas_x86_64
