#pragma once

#include <memory>

#include "../../../flow/typed_stage.hpp"
#include "../../context/base_context.h"
#include "../tokens.hpp"

namespace lib::lang::frontend {

template <typename TokenType, typename AstNode, ContextLike Context>
class Parser : public flow::TypedStage<Parser<TokenType, AstNode, Context>, Context,
                   Tokens<TokenType>, std::shared_ptr<AstNode>> {
public:
    virtual std::shared_ptr<AstNode> Run(Tokens<TokenType> tokens, Context& ctx) const = 0;
};

}  // namespace lib::lang::frontend
