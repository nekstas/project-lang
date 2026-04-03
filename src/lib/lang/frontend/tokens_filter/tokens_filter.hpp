#pragma once

#include "../../../flow/typed_stage.hpp"
#include "../../context/base_context.h"
#include "../../types.hpp"

namespace lib::lang::frontend {

template <typename TokenType, ContextLike Context>
class TokensFilter : public flow::TypedStage<TokensFilter<TokenType, Context>, Context,
                         t::Tokens<TokenType>, t::Tokens<TokenType>> {
public:
    virtual t::Tokens<TokenType> Run(t::Tokens<TokenType> tokens, Context& ctx) const = 0;
};

}  // namespace lib::lang::frontend
