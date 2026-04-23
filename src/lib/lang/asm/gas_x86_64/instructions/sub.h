#pragma once

#include "../dst_src_op.h"

namespace lib::lang::asm_::gas_x86_64::instr {

class Sub : public OpDstSrc {
public:
    using OpDstSrc::OpDstSrc;

    std::string GetOp() const override {
        return "sub";
    }
};

}  // namespace lib::lang::asm_::gas_x86_64::instr
