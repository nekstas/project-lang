#pragma once

#include <sstream>

#include "../../../lib/utils/indentable.h"
#include "../../fwd.h"
#include "../visitor.h"

namespace lang::ast::visitors {

class AstPrinter : public ::utils::Indentable, public Visitor {
public:
    using Indentable::Indentable;

    std::string ToString(const Node* node);

public:
    void Visit(const Program& program) override;

    void Visit(const expr::lit::IntLiteral& lit) override;
    void Visit(const expr::BinaryExpression& expr) override;
    void Visit(const expr::UnaryExpression& expr) override;
    void Visit(const expr::FunctionCallExpression& expr) override;
    void Visit(const expr::VariableExpression& expr) override;

    void Visit(const stmt::FunctionDefineNode& stmt) override;
    void Visit(const stmt::IfStatement& stmt) override;
    void Visit(const stmt::IfElseStatement& stmt) override;
    void Visit(const stmt::WhileStatement& stmt) override;
    void Visit(const stmt::BlockStatement& stmt) override;
    void Visit(const stmt::VariableDeclareStatement& stmt) override;
    void Visit(const stmt::AssignmentStatement& stmt) override;
    void Visit(const stmt::ReturnStatement& stmt) override;
    void Visit(const stmt::FunctionCallStatement& stmt) override;

private:
    std::stringstream out_;
};

}  // namespace lang::ast::visitors
