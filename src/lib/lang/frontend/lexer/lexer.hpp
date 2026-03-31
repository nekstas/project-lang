#pragma once

#include "../../../flow/typed_stage.hpp"
#include "../../context/base_context.h"
#include "../tokens.hpp"

namespace lib::lang::frontend {

template <typename TokenType, ContextLike Context>
class Lexer
    : public flow::TypedStage<Lexer<TokenType, Context>, Context, SourceDesc, Tokens<TokenType>> {
public:
    virtual Tokens<TokenType> Run(SourceDesc desc, Context& ctx) const = 0;
};

}  // namespace lib::lang::frontend
