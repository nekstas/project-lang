#pragma once

#include <memory>

#include "../../../flow/typed_stage.hpp"
#include "../../context/base_context.h"
#include "../../types.hpp"

namespace lib::lang::frontend {

template <typename TokenType, typename NodeType, ContextLike Context>
class Parser : public flow::TypedStage<Parser<TokenType, NodeType, Context>, Context,
                   t::Tokens<TokenType>, std::unique_ptr<NodeType>> {
public:
    using NodePtr = std::unique_ptr<NodeType>;

public:
    virtual NodePtr Run(t::Tokens<TokenType> tokens, Context& ctx) const = 0;
};

}  // namespace lib::lang::frontend
