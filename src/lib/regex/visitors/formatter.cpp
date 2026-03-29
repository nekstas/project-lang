#include "formatter.h"

#include "../../errors/errors.h"
#include "../../utils/utils.h"
#include "../ast/all.h"
#include "../utils/utils.h"

namespace lib::regex::visitors {

namespace {

constexpr std::string kSpecialSetChars = "\\\n\t\r\f\v]^";
constexpr std::string kSpecialCommonChars = "\\\n\t\r\f\v(|)*+?[";

}  // namespace

std::string Formatter::ToString(const ast::Node* node) {
    out_.str("");
    if (node != nullptr) {
        node->Accept(*this);
    }
    return out_.str();
}

std::string CharToCommonRepr(uint8_t code) {
    ::utils::FormatStream out;
    if (::utils::IsIn(code, kSpecialCommonChars)) {
        out << utils::GetSpecialCharRepr(code);
    } else if (std::isprint(code)) {
        out << code;
    } else {
        out << "\\x" << utils::EscapeHexByte(code);
    }
    return out;
}

std::string CharToSetCharsRepr(uint8_t code, bool is_first) {
    ::utils::FormatStream out;
    if (::utils::IsIn(code, kSpecialSetChars) && (is_first || code != '^')) {
        out << utils::GetSpecialCharRepr(code);
    } else if (std::isprint(code)) {
        out << code;
    } else {
        out << "\\x" << utils::EscapeHexByte(code);
    }
    return out;
}

void Formatter::Visit(const ast::CharNode& node) {
    out_ << CharToCommonRepr(node.GetCode());
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

void Formatter::Visit(const ast::CharSetNode& node) {
    out_ << "[";
    if (node.GetNegated()) {
        out_ << "^";
    }
    bool is_first = !node.GetNegated();
    for (const auto& range : ast::ToSpecialRanges(node.GetMask())) {
        out_ << CharToSetCharsRepr(range.GetFrom(), is_first);
        switch (range.Length()) {
            case 0:
                UNREACHABLE;
            case 1:
                break;
            case 2:
                out_ << CharToSetCharsRepr(range.GetTo(), false);
                break;
            default:
                out_ << "-" << CharToSetCharsRepr(range.GetTo(), false);
        }
        is_first = false;
    }
    out_ << "]";
}

void Formatter::Visit(const ast::CharClassNode& node) {
    auto repr = ast::CharClassToRepr(node.GetCharClass(), node.GetNegated());
    out_ << repr;
}

}  // namespace lib::regex::visitors
