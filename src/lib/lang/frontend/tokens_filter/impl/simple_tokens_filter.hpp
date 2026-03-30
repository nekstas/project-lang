#pragma once

#include <unordered_set>

#include "../../../context/base_context.h"
#include "../../tokens.hpp"
#include "../tokens_filter.hpp"

namespace lib::lang::frontend::impl {

template <typename TokenType, ContextLike Context>
class SimpleTokensFilter : public TokensFilter<TokenType, Context> {
public:
    Tokens<TokenType> Run(Tokens<TokenType> tokens, Context& ctx) const override {
        Tokens<TokenType> result;
        for (const auto& token : tokens) {
            if (!denied_tokens_.contains(token.GetType())) {
                result.push_back(token);
            }
        }
        return result;
    }

    std::string Name() const override {
        return "SimpleTokensFilter";
    }

protected:
    void DenyToken(TokenType token_type) {
        denied_tokens_.insert(token_type);
    }

public:
    std::unordered_set<TokenType> denied_tokens_;
};

}  // namespace lib::lang::frontend::impl
