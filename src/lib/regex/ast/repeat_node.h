#pragma once

#include <memory>
#include <vector>

#include "../visitors/visitor.h"
#include "node.h"

namespace lang::regex::ast {

enum class RepeatType { ZERO_OR_MORE, ONE_OR_MORE, ZERO_OR_ONE };

class RepeatNode : public Node {
public:
    RepeatNode(std::unique_ptr<Node> node, RepeatType repeat_type);

    bool Equals(const Node* another_node) const override;

    void Accept(lang::regex::visitors::Visitor& visitor) const override {
        visitor.Visit(*this);
    }

    const Node& GetNode() const {
        return *node_.get();
    }

    RepeatType GetRepeatType() const {
        return repeat_type_;
    }

private:
    void EnsureInvariants();

public:
    std::unique_ptr<Node> node_;
    RepeatType repeat_type_;
};

}  // namespace lang::regex::ast
