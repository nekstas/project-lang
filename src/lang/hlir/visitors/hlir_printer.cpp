#include "../expr/lit/int_literal.h"
#include "hlir_printer.h"

namespace lang::hlir::visitors {

std::string HlirPrinter::ToString(const Node* node) {
    out_.str("");
    if (node == nullptr) {
        Line(out_) << "[Null]";
    } else {
        node->Accept(*this);
    }
    return out_.str();
}

void HlirPrinter::Visit(const expr::lit::IntLiteral& lit) {
    Line(out_) << "[IntLiteral " << lit.GetValue() << "]";
}

}  // namespace lang::hlir::visitors
