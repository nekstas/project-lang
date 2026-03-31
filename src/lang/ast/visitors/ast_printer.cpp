#include "ast_printer.h"

#include <iomanip>

#include "../../../lib/utils/indentable.h"
#include "../expr/binary_expression.h"
#include "../expr/lit/int_literal.h"

namespace lang::ast::visitors {

std::string AstPrinter::ToString(const Node* node) {
    out_.str("");
    if (node == nullptr) {
        Line(out_) << "<Null>";
    } else {
        node->Accept(*this);
    }
    return out_.str();
}

void AstPrinter::Visit(const expr::lit::IntLiteral& lit) {
    Line(out_) << "<IntLiteral \"" << lit.GetValue() << "\">";
}

void AstPrinter::Visit(const expr::BinaryExpression& expr) {
    Line(out_) << "<BinaryExpression \"" << expr.GetOperation() << "\">";
    {
        utils::WithIndent with_indent{*this};
        expr.GetLeftExpression().Accept(*this);
        expr.GetRightExpression().Accept(*this);
    }
    Line(out_) << "</BinaryExpression>";
}

}  // namespace lang::ast::visitors
