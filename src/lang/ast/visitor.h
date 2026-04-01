#pragma once

#include "../fwd.h"

namespace lang::ast {

class Visitor {
public:
    virtual ~Visitor() {}

    virtual void Visit(const Program& program) = 0;

    virtual void Visit(const expr::lit::IntLiteral& expr) = 0;
    virtual void Visit(const expr::BinaryExpression& expr) = 0;
    virtual void Visit(const expr::UnaryExpression& expr) = 0;
    virtual void Visit(const expr::FunctionCallExpression& expr) = 0;
    virtual void Visit(const expr::VariableExpression& expr) = 0;

    virtual void Visit(const stmt::FunctionDefineNode& stmt) = 0;
    virtual void Visit(const stmt::IfStatement& stmt) = 0;
    virtual void Visit(const stmt::IfElseStatement& stmt) = 0;
    virtual void Visit(const stmt::WhileStatement& stmt) = 0;
    virtual void Visit(const stmt::BlockStatement& stmt) = 0;
    virtual void Visit(const stmt::VariableDeclareStatement& stmt) = 0;
    virtual void Visit(const stmt::AssignmentStatement& stmt) = 0;
    virtual void Visit(const stmt::ReturnStatement& stmt) = 0;
    virtual void Visit(const stmt::FunctionCallStatement& stmt) = 0;
};

}  // namespace lang::ast
