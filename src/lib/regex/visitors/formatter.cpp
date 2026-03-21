#include "formatter.h"

#include "../../utils/utils.h"
#include "../ast/all.h"
#include "../utils/utils.h"

namespace lang::regex::visitors {

namespace {

constexpr std::string kSpecialChars = "\\\n\t(|)*+?";

}

std::string Formatter::ToString(const ast::Node* node) {
    out_.str("");
    if (node != nullptr) {
        node->Accept(*this);
    }
    return out_.str();
}

void Formatter::Visit(const ast::CharNode& node) {
    const auto code = node.GetCode();
    if (::utils::IsIn(code, kSpecialChars)) {
        out_ << lang::regex::utils::GetSpecialCharRepr(code);
    } else {
        out_ << node.GetCode();
    }
}

void Formatter::Visit(const ast::WideCharNode& node) {
    out_ << node.GetWideChar();
}

void Formatter::Visit(const ast::ChoiceNode& node) {
    bool is_first = true;
    out_ << "(";
    for (const auto& another_node : node.GetNodes()) {
        if (!is_first) {
            out_ << "|";
        }
        another_node->Accept(*this);
        is_first = false;
    }
    out_ << ")";
}

void Formatter::Visit(const ast::RepeatNode& node) {
    const auto& inner_node = node.GetNode();
    bool use_brackets = ast::CastNode<ast::SequenceNode>(&inner_node);
    if (use_brackets) {
        out_ << "(";
    }
    inner_node.Accept(*this);
    if (use_brackets) {
        out_ << ")";
    }
    out_ << ast::RepeatTypeToChar(node.GetRepeatType());
}

void Formatter::Visit(const ast::SequenceNode& node) {
    for (const auto& another_node : node.GetNodes()) {
        another_node->Accept(*this);
    }
}

}  // namespace lang::regex::visitors
