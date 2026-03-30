#include "ast_printer.h"

#include "../../errors/errors.h"
#include "../../utils/utils.h"
#include "../ast/all.h"
#include "../ast/char_set_node.h"

namespace lib::regex {

namespace {

constexpr std::string kSpecialChars = "\\\n\t\r\f\v'";

std::string CharToRepr(uint8_t code) {
    ::utils::FormatStream out;
    if (::utils::IsIn(code, kSpecialChars)) {
        out << "'" << ::utils::GetSpecialCharRepr(code) << "'";
    } else if (std::isprint(code)) {
        out << "'" << code << "'";
    } else {
        out << "(" << static_cast<size_t>(code) << ")";
    }
    return out;
}

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
    Line(out_) << "[" << CharToRepr(node.GetCode()) << "]";
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

void visitors::AstPrinter::Visit(const ast::CharSetNode &node) {
    Line(out_) << "[char_set" << (node.GetNegated() ? " ^" : "") << "]";
    {
        utils::WithIndent with_indent(*this);
        for (const auto &range : ast::ToSpecialRanges(node.GetMask())) {
            switch (range.Length()) {
                case 0:
                    UNREACHABLE;
                case 1:
                    Line(out_) << "[" << CharToRepr(range.GetDot()) << "]";
                    break;
                case 2:
                    Line(out_) << "[" << CharToRepr(range.GetFrom()) << "]["
                               << CharToRepr(range.GetTo()) << "]";
                    break;
                default:
                    Line(out_) << "[" << CharToRepr(range.GetFrom()) << "-"
                               << CharToRepr(range.GetTo()) << "]";
            }
        }
    }
    Line(out_) << "[/char_set]";
}

void visitors::AstPrinter::Visit(const ast::CharClassNode &node) {
    auto repr = ast::CharClassToRepr(node.GetCharClass(), node.GetNegated());
    Line(out_) << "[char_class " << repr << "]";
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
