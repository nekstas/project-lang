#pragma once

#include "../visitors/visitor.h"
#include "nodes_base_node.h"

namespace lib::regex::ast {

class ChoiceNode : public NodesBaseNode {
public:
    using NodesBaseNode::NodesBaseNode;

    bool Equals(const Node* another_node) const override {
        return NodesBaseNode::Equals(another_node) && CastNode<ChoiceNode>(another_node);
    }

    void Accept(visitors::Visitor& visitor) const override {
        visitor.Visit(*this);
    }
};

}  // namespace lib::regex::ast
