#pragma once

#include "../fwd.h"

namespace lib::lang::llir {

class Visitor {
public:
    virtual ~Visitor() {}

    virtual void Visit(const instr::LoadInt64& instr) = 0;
};

}  // namespace lib::lang::llir
