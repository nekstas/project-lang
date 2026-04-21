#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "instruction.hpp"

namespace lib::lang::llir {

class InstructionSequence {
public:
    template <typename InstructionType, typename... Args>
    void AddInstruction(Args&&... args) {
        AddInstruction(std::make_unique<InstructionType>(std::forward<Args>(args)...));
    }

    void AddInstruction(std::unique_ptr<Instruction> instruction);

    size_t Size() const {
        return instructions_.size();
    }

    const std::vector<std::unique_ptr<Instruction>>& GetInstructions() const {
        return instructions_;
    }

private:
    std::vector<std::unique_ptr<Instruction>> instructions_;
};

std::ostream& operator<<(std::ostream& out, const InstructionSequence& instruction_sequence);

}  // namespace lib::lang::llir
