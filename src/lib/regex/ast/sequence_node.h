#pragma once

#include <memory>
#include <vector>

#include "../visitors/visitor.h"
#include "nodes_base_node.h"

namespace lang::regex::ast {

class SequenceNode : public NodesBaseNode {
public:
    using NodesBaseNode::NodesBaseNode;

    bool Equals(const Node* another_node) const override {
        return NodesBaseNode::Equals(another_node) && CastNode<SequenceNode>(another_node);
    }

    void Accept(lang::regex::visitors::Visitor& visitor) const override {
        visitor.Visit(*this);
    }
};

}  // namespace lang::regex::ast
