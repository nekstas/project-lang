#pragma once

#include <string>

#include "../visitors/visitor.h"
#include "node.h"

namespace lib::regex::ast {

class WideCharNode : public Node {
public:
    WideCharNode(const std::string& wide_char) : wide_char_(wide_char) {}

    bool Equals(const Node* another_node) const override {
        const auto char_node = CastNode<WideCharNode>(another_node);
        return char_node && GetWideChar() == char_node->GetWideChar();
    }

    void Accept(visitors::Visitor& visitor) const override {
        visitor.Visit(*this);
    }

    std::string GetWideChar() const {
        return wide_char_;
    }

private:
    std::string wide_char_;
};

}  // namespace lib::regex::ast
