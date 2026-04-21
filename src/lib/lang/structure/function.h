#pragma once

#include <optional>

#include "../cfg/control_flow_graph.h"
#include "../symbols/descriptors/function_descriptor.h"
#include "instruction_sequence.h"

namespace lib::lang::structure {

class Function {
public:
    Function(symbols::FunctionDescriptor* desc, InstructionSequence body)
        : desc_(desc), body_(std::make_unique<InstructionSequence>(std::move(body))) {}

    const symbols::FunctionDescriptor* GetDesc() const {
        return desc_;
    }

    const InstructionSequence& GetBody() const {
        return *body_;
    }

    const cfg::ControlFlowGraph& GetCfg() const {
        if (cfg_ == std::nullopt) {
            cfg_ = cfg::ControlFlowGraph::BuildFrom(*body_);
        }
        return *cfg_;
    }

    void InvalidateCfg() const {
        cfg_ = std::nullopt;
    }

private:
    symbols::FunctionDescriptor* desc_;
    std::unique_ptr<InstructionSequence> body_;
    mutable std::optional<cfg::ControlFlowGraph> cfg_;
};

std::ostream& operator<<(std::ostream& out, const Function& function);

}  // namespace lib::lang::structure
