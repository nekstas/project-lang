#pragma once
#include "../structure/instruction_sequence.h"

namespace lib::lang::cfg {

class BasicBlock {
    friend class ControlFlowGraph;

private:
    BasicBlock(size_t begin, size_t end, const structure::InstructionSequence& instruction_sequence)
        : begin_(begin), end_(end), instruction_sequence_(instruction_sequence) {}

public:
    std::vector<llir::Instruction*> GetInstructions() const {
        const auto& all_instructions = instruction_sequence_.GetInstructions();
        std::vector<llir::Instruction*> result;
        for (size_t i = begin_; i < end_; ++i) {
            result.push_back(all_instructions[i].get());
        }
        return result;
    }

private:
    size_t begin_;
    size_t end_;
    const structure::InstructionSequence& instruction_sequence_;
};

}  // namespace lib::lang::cfg
