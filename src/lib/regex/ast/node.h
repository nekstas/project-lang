#pragma once

#include "../fwd.h"

namespace lang::regex::ast {

class Node {
public:
    virtual ~Node() {}

    virtual bool Equals(const Node* another_node) const = 0;
    virtual void Accept(lang::regex::visitors::Visitor& visitor) const = 0;
};

template <typename T>
const T* CastNode(const Node* node) {
    return dynamic_cast<const T*>(node);
}

template <typename T>
T* CastNode(Node* node) {
    return dynamic_cast<T*>(node);
}

}  // namespace lang::regex::ast
