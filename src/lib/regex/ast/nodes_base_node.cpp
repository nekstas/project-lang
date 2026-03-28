#include "nodes_base_node.h"

#include <cassert>

#include "../../errors/errors.h"

namespace lib::regex::ast {

namespace {

bool NodesEqual(const std::vector<std::unique_ptr<Node>>& lhs,
                const std::vector<std::unique_ptr<Node>>& rhs) {
    if (lhs.size() != rhs.size()) {
        return false;
    }
    for (size_t i = 0; i < lhs.size(); ++i) {
        assert(lhs[i] && rhs[i]);
        if (!lhs[i]->Equals(rhs[i].get())) {
            return false;
        }
    }
    return true;
}

}  // namespace

NodesBaseNode::NodesBaseNode(std::vector<std::unique_ptr<Node>> arg_nodes)
    : nodes_(std::move(arg_nodes)) {
    EnsureInvariants();
}

bool NodesBaseNode::Equals(const Node* another_node) const {
    const auto nodes_base_node = CastNode<NodesBaseNode>(another_node);
    return nodes_base_node && NodesEqual(GetNodes(), nodes_base_node->GetNodes());
}

void NodesBaseNode::EnsureInvariants() const {
    THROW_IF(nodes_.size() <= 1, ::errors::LogicError,
             "Nodes list should contain at least two nodes.");
    for (size_t i = 0; i < nodes_.size(); ++i) {
        THROW_IF(!nodes_[i], ::errors::LogicError, "Node with index" << i << "is nullptr.");
    }
}

}  // namespace lib::regex::ast
