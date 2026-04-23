#pragma once

#include <vector>

#include "basic_block.h"

namespace lib::lang::cfg {

class ControlFlowGraph {
private:
    explicit ControlFlowGraph(std::vector<BasicBlock> blocks) : blocks_(std::move(blocks)) {}

public:
    const BasicBlock& GetFirstBlock() const {
        return GetBlock(0);
    }

    const BasicBlock& GetBlock(size_t index) const {
        return blocks_[index];
    }

public:
    static ControlFlowGraph BuildFrom(const structure::InstructionSequence& instruction_sequence) {
        std::vector<BasicBlock> blocks;
        blocks.push_back(BasicBlock{0, instruction_sequence.Size(), instruction_sequence});
        return ControlFlowGraph{std::move(blocks)};
    }

private:
    std::vector<BasicBlock> blocks_ = {};
};

}  // namespace lib::lang::cfg
