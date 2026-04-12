#pragma once

#include "../fwd.h"

namespace lib::lang::cst {

template <typename TokenType, typename RuleType>
class Node {
public:
    virtual ~Node() {}

    // virtual void Accept(Visitor& visitor) const = 0;
};

template <typename T, typename TokenType, typename RuleType>
const T* CastNode(const Node<TokenType, RuleType>* node) {
    return dynamic_cast<const T*>(node);
}

template <typename T, typename TokenType, typename RuleType>
T* CastNode(Node<TokenType, RuleType>* node) {
    return dynamic_cast<T*>(node);
}

}  // namespace lib::lang::cst
