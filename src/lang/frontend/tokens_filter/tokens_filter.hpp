#pragma once

#include "../../../lib/lang/context/base_context.h"
#include "../../../lib/lang/frontend/tokens_filter/impl/simple_tokens_filter.hpp"
#include "../../token_type.h"

namespace lang::frontend {

template <lib::lang::ContextLike Context>
class TokensFilter : public lib::lang::frontend::impl::SimpleTokensFilter<TokenType, Context> {
private:
    using Super = lib::lang::frontend::impl::SimpleTokensFilter<TokenType, Context>;

public:
    TokensFilter() {
        FillDeniedTokens();
    }

private:
    void FillDeniedTokens() {
        Super::DenyToken(TokenType::WHITESPACE);
        Super::DenyToken(TokenType::NEW_LINE);
    }
};

}  // namespace lang::frontend
