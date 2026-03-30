#pragma once

#include "../../../flow/typed_stage.hpp"
#include "../../context/base_context.h"
#include "../tokens.hpp"

namespace lib::lang::frontend {

template <typename TokenType, ContextLike Context>
class TokensFilter : public flow::TypedStage<TokensFilter<TokenType, Context>, Context,
                         Tokens<TokenType>, Tokens<TokenType>> {
public:
    virtual Tokens<TokenType> Run(Tokens<TokenType> tokens, Context& ctx) const = 0;
};

}  // namespace lib::lang::frontend
