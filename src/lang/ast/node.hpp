#pragma once

#include "../fwd.h"

namespace lang::ast {

class Node {
public:
    virtual ~Node() {}

    virtual void Accept(Visitor& visitor) const = 0;
};

template <typename T>
const T* CastNode(const Node* node) {
    return dynamic_cast<const T*>(node);
}

template <typename T>
T* CastNode(Node* node) {
    return dynamic_cast<T*>(node);
}

}  // namespace lang::ast
