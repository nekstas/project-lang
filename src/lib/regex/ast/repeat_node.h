#pragma once

#include <memory>

#include "../visitors/visitor.h"
#include "node.h"

namespace lib::regex::ast {

enum class RepeatType { ZERO_OR_MORE, ONE_OR_MORE, ZERO_OR_ONE };

uint8_t RepeatTypeToChar(RepeatType repeat_type);

RepeatType RepeatCharToType(uint8_t repeat_char);

class RepeatNode : public Node {
public:
    RepeatNode(std::unique_ptr<Node> node, RepeatType repeat_type);

    bool Equals(const Node* another_node) const override;

    void Accept(visitors::Visitor& visitor) const override {
        visitor.Visit(*this);
    }

    const Node& GetNode() const {
        return *node_.get();
    }

    RepeatType GetRepeatType() const {
        return repeat_type_;
    }

private:
    void EnsureInvariants() const;

private:
    std::unique_ptr<Node> node_;
    RepeatType repeat_type_;
};

}  // namespace lib::regex::ast
