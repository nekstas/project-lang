#pragma once

#include "../../../lib/lang/context/base_context.h"
#include "../../../lib/lang/frontend/tokens_filter/impl/simple_tokens_filter.hpp"
#include "../../enums/token_type.h"

namespace lang::frontend {

template <lib::lang::ContextLike Context>
class SimpleTokensFilter
    : public lib::lang::frontend::impl::SimpleTokensFilter<e::TokenType, Context> {
private:
    using Super = lib::lang::frontend::impl::SimpleTokensFilter<e::TokenType, Context>;

public:
    SimpleTokensFilter() {
        FillDeniedTokens();
    }

private:
    void FillDeniedTokens() {
        Super::DenyToken(e::TokenType::WHITESPACE);
        Super::DenyToken(e::TokenType::NEW_LINE);
    }
};

}  // namespace lang::frontend
