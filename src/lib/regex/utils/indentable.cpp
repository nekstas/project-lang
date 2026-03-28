#include "indentable.h"

#include <cassert>
#include <iostream>

namespace lib::regex::utils {

namespace {
constexpr std::string kNewLine = "\n";
}

WithIndent::WithIndent(Indentable& ast_printer) : ast_printer_(ast_printer) {
    ast_printer_.AddIndent();
}

WithIndent::~WithIndent() {
    ast_printer_.RemoveIndent();
}

Indentable::Indentable(size_t indent_spaces, bool use_newlines)
    : indent_step_(indent_spaces, ' '), use_newlines_(use_newlines) {}

Indentable::Indentable(const std::string& indent_step, bool use_newlines)
    : indent_step_(indent_step), use_newlines_(use_newlines) {}

void Indentable::AddIndent() {
    indent_.append(indent_step_);
}

void Indentable::RemoveIndent() {
    assert(indent_.size() >= indent_step_.size());
    indent_.resize(indent_.size() - indent_step_.size());
}

LinePrinter Indentable::Line(std::ostream& out) {
    return {indent_, use_newlines_, out};
}

LinePrinter::LinePrinter(const std::string& indent, bool use_newlines, std::ostream& out)
    : use_newlines_(use_newlines), out_(out) {
    out_ << indent;
}

LinePrinter::~LinePrinter() {
    if (use_newlines_) {
        out_ << kNewLine;
    }
}

}  // namespace lib::regex::utils
