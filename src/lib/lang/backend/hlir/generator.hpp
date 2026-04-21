#pragma once

#include <memory>

#include "../../../../lib/flow/typed_stage.hpp"
#include "../../context/base_context.h"

namespace lib::lang::backend::hlir {

template <typename AstNodeType, typename HlirNodeType, ContextLike Context>
class Generator : public flow::TypedStage<Generator<AstNodeType, HlirNodeType, Context>, Context,
                      std::unique_ptr<AstNodeType>, std::unique_ptr<HlirNodeType>> {
public:
    using AstNodePtr = std::unique_ptr<AstNodeType>;
    using HlirNodePtr = std::unique_ptr<HlirNodeType>;

public:
    virtual HlirNodePtr Run(AstNodePtr ast, Context& ctx) const = 0;

    std::string Name() const override {
        return "HlirGenerator";
    }
};

}  // namespace lib::lang::backend::hlir
