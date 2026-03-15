#include "ast_printer.h"

#include "../../errors/errors.h"
#include "../ast/all.h"

namespace lang::regex {

namespace {

uint8_t RepeatTypeToChar(const ast::RepeatType repeat_type) {
    switch (repeat_type) {
        case ast::RepeatType::ZERO_OR_MORE:
            return '*';
        case ast::RepeatType::ONE_OR_MORE:
            return '+';
        case ast::RepeatType::ZERO_OR_ONE:
            return '?';
        default:
            THROW(errors::LogicError, "");
    }
}

}  // namespace

std::string visitors::AstPrinter::ToString(ast::Node *node) {
    out_.clear();
    utils::WithIndent{*this};
    if (node == nullptr) {
        Line(out_) << "[null]";
    } else {
        node->Accept(*this);
    }
    return out_.str();
}

void visitors::AstPrinter::Visit(const ast::CharNode &node) {
    const auto code = node.GetCode();
    if (std::isprint(code)) {
        Line(out_) << "['" << code << "']";
    } else {
        Line(out_) << "[(" << static_cast<size_t>(code) << ")]";
    }
}

void visitors::AstPrinter::ProcessNodesBaseNode(const lang::regex::ast::NodesBaseNode &node) {
    utils::WithIndent with_indent(*this);
    for (const auto &item : node.GetNodes()) {
        item->Accept(*this);
    }
}

void visitors::AstPrinter::Visit(const ast::ChoiceNode &node) {
    Line(out_) << "[choice]";
    ProcessNodesBaseNode(node);
    Line(out_) << "[/choice]";
}

void visitors::AstPrinter::Visit(const ast::SequenceNode &node) {
    Line(out_) << "[seq]";
    ProcessNodesBaseNode(node);
    Line(out_) << "[/seq]";
}

void visitors::AstPrinter::Visit(const ast::RepeatNode &node) {
    const auto repeat_char = RepeatTypeToChar(node.GetRepeatType());
    Line(out_) << "[repeat " << repeat_char << "]";
    {
        utils::WithIndent with_indent(*this);
        node.GetNode().Accept(*this);
    }
    Line(out_) << "[/repeat ]";
}

}  // namespace lang::regex
