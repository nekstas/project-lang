#pragma once

#include "../../fwd.h"
#include "../node.hpp"

namespace lib::lang::cst::nodes {

template <typename TokenType, typename RuleType>
class RuleNode : public Node<TokenType, RuleType> {
public:
    // virtual void Accept(Visitor& visitor) const = 0;
};

}  // namespace lib::lang::cst
