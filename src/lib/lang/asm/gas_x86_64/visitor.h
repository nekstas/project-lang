#pragma once

#include "fwd.h"

namespace lib::lang::asm_::gas_x86_64 {

class Visitor {
public:
    virtual ~Visitor() {}

    virtual void Visit(const Label& label) = 0;

    virtual void Visit(const dir::IntelSyntax& dir) = 0;
    virtual void Visit(const dir::Global& dir) = 0;
    virtual void Visit(const dir::Section& dir) = 0;

    virtual void Visit(const OpDstSrc& instr) = 0;
    virtual void Visit(const instr::Push& instr) = 0;
    virtual void Visit(const instr::Pop& instr) = 0;
    virtual void Visit(const instr::Ret& instr) = 0;
};

}  // namespace lib::lang::asm_::gas_x86_64
