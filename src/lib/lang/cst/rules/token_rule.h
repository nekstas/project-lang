#pragma once

#include "../../fwd.h"
#include "../../types.hpp"
#include "../rule.hpp"

namespace lib::lang::cst::rules {

template <typename TokenType, typename RuleType>
class TokenRule : public Rule<TokenType, RuleType> {
public:
    explicit TokenRule(const t::Token<TokenType>& token) : token_(token) {}

    const t::Token<TokenType>& GetToken() const {
        return token_;
    }

    // virtual void Accept(Visitor& visitor) const = 0;

private:
    t::Token<TokenType> token_;
};

}  // namespace lib::lang::cst::rules
