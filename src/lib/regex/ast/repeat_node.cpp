#include "repeat_node.h"

#include "../../errors/errors.h"

namespace lang::regex::ast {

uint8_t RepeatTypeToChar(const ast::RepeatType repeat_type) {
    switch (repeat_type) {
        case ast::RepeatType::ZERO_OR_MORE:
            return '*';
        case ast::RepeatType::ONE_OR_MORE:
            return '+';
        case ast::RepeatType::ZERO_OR_ONE:
            return '?';
        default:
            UNREACHABLE;
    }
}

ast::RepeatType RepeatCharToType(const uint8_t repeat_char) {
    switch (repeat_char) {
        case '*':
            return ast::RepeatType::ZERO_OR_MORE;
        case '+':
            return ast::RepeatType::ONE_OR_MORE;
        case '?':
            return ast::RepeatType::ZERO_OR_ONE;
        default:
            UNREACHABLE;
    }
}

RepeatNode::RepeatNode(std::unique_ptr<Node> node, RepeatType repeat_type)
    : node_(std::move(node)), repeat_type_(repeat_type) {
    EnsureInvariants();
}

bool RepeatNode::Equals(const Node *another_node) const {
    const auto repeat_node = CastNode<RepeatNode>(another_node);
    return repeat_node && GetRepeatType() == repeat_node->GetRepeatType() &&
           GetNode().Equals(&repeat_node->GetNode());
}

void RepeatNode::EnsureInvariants() {
    THROW_IF(!node_, ::errors::LogicError, "RepeatNode's inner node is nullptr.");
    THROW_IF(CastNode<RepeatNode>(node_.get()), ::errors::LogicError,
             "RepeatNode can't be inside another RepeatNode.");
}

}  // namespace lang::regex::ast
