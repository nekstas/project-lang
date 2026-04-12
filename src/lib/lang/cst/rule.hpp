#pragma once

#pragma once

#include "../fwd.h"

namespace lib::lang::cst {

template <typename TokenType, typename RuleType>
class Rule {
public:
    virtual ~Rule() {}

    // virtual void Accept(Visitor& visitor) const = 0;
};

template <typename T, typename TokenType, typename RuleType>
const T* CastRule(const Rule<TokenType, RuleType>* node) {
    return dynamic_cast<const T*>(node);
}

template <typename T, typename TokenType, typename RuleType>
T* CastRule(Rule<TokenType, RuleType>* node) {
    return dynamic_cast<T*>(node);
}

}  // namespace lib::lang::cst

