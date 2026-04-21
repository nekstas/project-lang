#pragma once

#include <sstream>
#include <string>

#include "../visitor.h"

namespace lib::lang::llir::visitors {

class InstructionStringifier : public Visitor {
public:
    std::string ToString(const Instruction* instr);

public:
    void Visit(const instr::LoadInt64& instr) override;

private:
    std::stringstream out_;
};

}  // namespace lib::lang::llir::visitors