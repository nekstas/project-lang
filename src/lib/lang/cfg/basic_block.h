#pragma once
#include "../structure/instruction_sequence.h"

namespace lib::lang::cfg {

class BasicBlock {
    friend class ControlFlowGraph;

private:
    BasicBlock(size_t begin, size_t end, const structure::InstructionSequence& instruction_sequence)
        : begin_(begin), end_(end), instruction_sequence_(instruction_sequence) {}

private:
    size_t begin_;
    size_t end_;
    const structure::InstructionSequence& instruction_sequence_;
};

}  // namespace lib::lang::cfg
