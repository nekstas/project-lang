#include "ast_printer.h"

#include "../../utils/utils.h"
#include "../ast/all.h"
#include "../utils/utils.h"

namespace lib::regex {

namespace {

constexpr std::string kSpecialChars = "\\\n\t'";

}  // namespace

std::string visitors::AstPrinter::ToString(const ast::Node *node) {
    out_.str("");
    if (node == nullptr) {
        Line(out_) << "[null]";
    } else {
        node->Accept(*this);
    }
    return out_.str();
}

void visitors::AstPrinter::Visit(const ast::CharNode &node) {
    const auto code = node.GetCode();
    if (::utils::IsIn(code, kSpecialChars)) {
        Line(out_) << "['" << utils::GetSpecialCharRepr(code) << "']";
    } else if (std::isprint(code)) {
        Line(out_) << "['" << code << "']";
    } else {
        Line(out_) << "[(" << static_cast<size_t>(code) << ")]";
    }
}

void visitors::AstPrinter::Visit(const ast::WideCharNode &node) {
    Line(out_) << "[\"" << node.GetWideChar() << "\"]";
}

void visitors::AstPrinter::ProcessNodesBaseNode(const ast::NodesBaseNode &node) {
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
    Line(out_) << "[/repeat]";
}

}  // namespace lib::regex
