#pragma once

#include <memory>
#include <vector>

#include "../visitors/visitor.h"
#include "node.h"

namespace lang::regex::ast {

class NodesBaseNode : public Node {
public:
    NodesBaseNode(std::vector<std::unique_ptr<Node>> arg_nodes);

    bool Equals(const Node* another_node) const override;

    const std::vector<std::unique_ptr<Node>>& GetNodes() const {
        return nodes_;
    }

    size_t GetSize() const {
        return nodes_.size();
    }

private:
    void EnsureInvariants();

protected:
    std::vector<std::unique_ptr<Node>> nodes_;
};

}  // namespace lang::regex::ast
