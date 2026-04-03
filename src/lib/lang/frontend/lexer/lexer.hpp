#pragma once

#include "../../../flow/typed_stage.hpp"
#include "../../context/base_context.h"
#include "../../types.hpp"

namespace lib::lang::frontend {

template <typename TokenType, ContextLike Context>
class Lexer
    : public flow::TypedStage<Lexer<TokenType, Context>, Context, SourceDesc, t::Tokens<TokenType>> {
public:
    virtual t::Tokens<TokenType> Run(SourceDesc desc, Context& ctx) const = 0;
};

}  // namespace lib::lang::frontend
