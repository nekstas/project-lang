#pragma once

#include "../../fwd.h"
#include "../../types.hpp"
#include "../node.hpp"

namespace lib::lang::cst::nodes {

template <typename TokenType, typename RuleType>
class TokenNode : public Node<TokenType, RuleType> {
public:
    explicit TokenNode(const t::Token<TokenType>& token) : token_(token) {}

    const t::Token<TokenType>& GetToken() const {
        return token_;
    }

    // virtual void Accept(Visitor& visitor) const = 0;

private:
    t::Token<TokenType> token_;
};

}  // namespace lib::lang::cst
