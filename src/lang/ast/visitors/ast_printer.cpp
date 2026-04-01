#include "ast_printer.h"

#include <cassert>
#include <iomanip>

#include "../../../lib/utils/indentable.h"
#include "../program.h"
#include "../expr/binary_expression.h"
#include "../expr/function_call_expression.h"
#include "../expr/lit/int_literal.h"
#include "../expr/variable_expression.h"
#include "../expr/unary_expression.h"
#include "../stmt/assignment_statement.h"
#include "../stmt/block_statement.h"
#include "../stmt/function_call_statement.h"
#include "../stmt/function_define_node.h"
#include "../stmt/if_else_statement.h"
#include "../stmt/if_statement.h"
#include "../stmt/return_statement.h"
#include "../stmt/variable_declare_statement.h"
#include "../stmt/while_statement.h"

namespace lang::ast::visitors {

std::string AstPrinter::ToString(const Node* node) {
    out_.str("");
    assert(node);
    node->Accept(*this);
    return out_.str();
}

void AstPrinter::Visit(const Program& program) {
    Line(out_) << "<Program>";
    {
        utils::WithIndent with_indent{*this};
        for (const auto& function : program.GetFunctions()) {
            function->Accept(*this);
        }
    }
    Line(out_) << "</Program>";
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

void AstPrinter::Visit(const expr::UnaryExpression& expr) {
    Line(out_) << "<UnaryExpression \"" << expr.GetOperation() << "\">";
    {
        utils::WithIndent with_indent{*this};
        expr.GetExpression().Accept(*this);
    }
    Line(out_) << "</UnaryExpression>";
}

void AstPrinter::Visit(const expr::FunctionCallExpression& expr) {
    Line(out_) << "<FunctionCallExpression " << std::quoted(expr.GetFunctionName()) << ">";
    {
        utils::WithIndent with_indent{*this};
        for (const auto& argument : expr.GetArguments()) {
            argument->Accept(*this);
        }
    }
    Line(out_) << "</FunctionCallExpression>";
}

void AstPrinter::Visit(const expr::VariableExpression& expr) {
    Line(out_) << "<VariableExpression " << std::quoted(expr.GetVariableName()) << ">";
}

void AstPrinter::Visit(const stmt::FunctionDefineNode& stmt) {
    Line(out_) << "<FunctionDefineNode " << std::quoted(stmt.GetFunctionName()) << ">";
    {
        utils::WithIndent with_indent{*this};
        if (stmt.GetReturnTypeName().has_value()) {
            Line(out_) << "<ReturnType " << std::quoted(*stmt.GetReturnTypeName()) << ">";
        } else {
            Line(out_) << "<ReturnType>";
        }
        Line(out_) << "<Parameters>";
        {
            utils::WithIndent with_indent_2{*this};
            for (const auto& parameter : stmt.GetParameters()) {
                auto line = Line(out_);
                line << "<Parameter " << std::quoted(parameter.name)
                     << " mutable=" << (parameter.is_mutable ? "true" : "false");
                if (parameter.type_name.has_value()) {
                    line << " type=" << std::quoted(*parameter.type_name);
                }
                line << ">";
            }
        }
        Line(out_) << "</Parameters>";
        stmt.GetBody().Accept(*this);
    }
    Line(out_) << "</FunctionDefineNode>";
}

void AstPrinter::Visit(const stmt::IfStatement& stmt) {
    Line(out_) << "<IfStatement>";
    {
        utils::WithIndent with_indent{*this};
        Line(out_) << "<Condition>";
        {
            utils::WithIndent with_indent_2{*this};
            stmt.GetCondition().Accept(*this);
        }
        Line(out_) << "</Condition>";
        stmt.GetThenBlock().Accept(*this);
    }
    Line(out_) << "</IfStatement>";
}

void AstPrinter::Visit(const stmt::IfElseStatement& stmt) {
    Line(out_) << "<IfElseStatement>";
    {
        utils::WithIndent with_indent{*this};
        Line(out_) << "<Condition>";
        {
            utils::WithIndent with_indent_2{*this};
            stmt.GetCondition().Accept(*this);
        }
        Line(out_) << "</Condition>";
        Line(out_) << "<Then>";
        {
            utils::WithIndent with_indent_2{*this};
            stmt.GetThenBlock().Accept(*this);
        }
        Line(out_) << "</Then>";
        Line(out_) << "<Else>";
        {
            utils::WithIndent with_indent_2{*this};
            stmt.GetElseBlock().Accept(*this);
        }
        Line(out_) << "</Else>";
    }
    Line(out_) << "</IfElseStatement>";
}

void AstPrinter::Visit(const stmt::WhileStatement& stmt) {
    Line(out_) << "<WhileStatement>";
    {
        utils::WithIndent with_indent{*this};
        Line(out_) << "<Condition>";
        {
            utils::WithIndent with_indent_2{*this};
            stmt.GetCondition().Accept(*this);
        }
        Line(out_) << "</Condition>";
        stmt.GetBody().Accept(*this);
    }
    Line(out_) << "</WhileStatement>";
}

void AstPrinter::Visit(const stmt::BlockStatement& stmt) {
    Line(out_) << "<BlockStatement>";
    {
        utils::WithIndent with_indent{*this};
        for (const auto& node : stmt.GetStatements()) {
            node->Accept(*this);
        }
    }
    Line(out_) << "</BlockStatement>";
}

void AstPrinter::Visit(const stmt::VariableDeclareStatement& stmt) {
    auto line = Line(out_);
    line << "<VariableDeclareStatement " << std::quoted(stmt.GetVariableName())
         << " mutable=" << (stmt.IsMutable() ? "true" : "false");
    if (stmt.GetTypeName().has_value()) {
        line << " type=" << std::quoted(*stmt.GetTypeName());
    }
    line << ">";
    {
        utils::WithIndent with_indent{*this};
        if (stmt.HasInitialValue()) {
            stmt.GetInitialValue().Accept(*this);
        }
    }
    Line(out_) << "</VariableDeclareStatement>";
}

void AstPrinter::Visit(const stmt::AssignmentStatement& stmt) {
    Line(out_) << "<AssignmentStatement " << std::quoted(stmt.GetVariableName()) << ">";
    {
        utils::WithIndent with_indent{*this};
        stmt.GetExpression().Accept(*this);
    }
    Line(out_) << "</AssignmentStatement>";
}

void AstPrinter::Visit(const stmt::ReturnStatement& stmt) {
    Line(out_) << "<ReturnStatement>";
    if (stmt.HasExpression()) {
        utils::WithIndent with_indent{*this};
        stmt.GetExpression().Accept(*this);
    }
    Line(out_) << "</ReturnStatement>";
}

void AstPrinter::Visit(const stmt::FunctionCallStatement& stmt) {
    Line(out_) << "<FunctionCallStatement>";
    {
        utils::WithIndent with_indent{*this};
        stmt.GetExpression().Accept(*this);
    }
    Line(out_) << "</FunctionCallStatement>";
}

}  // namespace lang::ast::visitors
