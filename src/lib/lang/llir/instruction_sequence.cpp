#include "instruction_sequence.h"

#include "visitors/instruction_stringifier.h"

namespace lib::lang::llir {
void InstructionSequence::AddInstruction(std::unique_ptr<Instruction> instruction) {
    instructions_.emplace_back(std::move(instruction));
}

std::ostream& operator<<(std::ostream& out, const InstructionSequence& instruction_sequence) {
    visitors::InstructionStringifier stringifier;
    out << "LLIR (" << instruction_sequence.Size() << ")\n";
    for (const auto& instruction : instruction_sequence.GetInstructions()) {
        out << stringifier.ToString(instruction.get()) << "\n";
    }
    return out;
}

}  // namespace lib::lang::llir
