#pragma once

#include <memory>

#include "../../../../lib/flow/typed_stage.hpp"
#include "../../context/base_context.h"
#include "../../llir/instruction_sequence.h"

namespace lib::lang::backend::llir {

template <typename HlirNodeType, ContextLike Context>
class Generator : public flow::TypedStage<Generator<HlirNodeType, Context>, Context,
                      std::unique_ptr<HlirNodeType>, lang::llir::InstructionSequence> {
public:
    using HlirNodePtr = std::unique_ptr<HlirNodeType>;

public:
    virtual lang::llir::InstructionSequence Run(HlirNodePtr hlir, Context& ctx) const = 0;

    std::string Name() const override {
        return "LlirGenerator";
    }
};

}  // namespace lib::lang::backend::llir
