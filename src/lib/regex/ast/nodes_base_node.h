#pragma once

#include <memory>
#include <vector>

#include "node.h"

namespace lib::regex::ast {

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
    void EnsureInvariants() const;

protected:
    std::vector<std::unique_ptr<Node>> nodes_;
};

}  // namespace lib::regex::ast
