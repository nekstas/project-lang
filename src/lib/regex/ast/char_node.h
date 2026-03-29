#pragma once

#include <cstdint>

#include "../visitors/visitor.h"
#include "node.h"

namespace lib::regex::ast {

class CharNode : public Node {
public:
    explicit CharNode(uint8_t code) : code_(code) {}

    bool Equals(const Node* another_node) const override {
        const auto char_node = CastNode<CharNode>(another_node);
        return char_node && GetCode() == char_node->GetCode();
    }

    void Accept(visitors::Visitor& visitor) const override {
        visitor.Visit(*this);
    }

    uint8_t GetCode() const {
        return code_;
    }

private:
    uint8_t code_;
};

}  // namespace lib::regex::ast
