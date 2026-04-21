#include "instruction_sequence.h"

#include "../llir/visitors/instruction_stringifier.h"

namespace lib::lang::structure {
void InstructionSequence::AddInstruction(std::unique_ptr<llir::Instruction> instruction) {
    instructions_.emplace_back(std::move(instruction));
}

std::ostream& operator<<(std::ostream& out, const InstructionSequence& instruction_sequence) {
    llir::visitors::InstructionStringifier stringifier;
    for (const auto& instruction : instruction_sequence.GetInstructions()) {
        out << stringifier.ToString(instruction.get()) << "\n";
    }
    return out;
}

}  // namespace lib::lang::structure
