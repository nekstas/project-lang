#pragma once

#include <cstdint>
#include <iostream>
#include <istream>
#include <ostream>
#include <stdexcept>
#include <string>
#include <unordered_map>
#include <vector>

#include "../../fwd.h"
#include "../visitor.h"

namespace lang::ast::visitors {

class InterpreterRuntimeError : public std::runtime_error {
public:
    explicit InterpreterRuntimeError(const std::string& message) : std::runtime_error(message) {}
};

class Interpreter : public Visitor {
public:
    explicit Interpreter(std::istream& in = std::cin, std::ostream& out = std::cout)
        : in_(in), out_(out) {}

    void Execute(const Node* node);

public:
    void Visit(const Program& program) override;

    void Visit(const expr::lit::IntLiteral& expr) override;
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
    using Int = std::int64_t;

    struct Variable {
        Int value;
        bool is_mutable;
    };

    using Scope = std::unordered_map<std::string, Variable>;

    Int Eval(const Expression& expression);
    static void ThrowRuntimeError(const std::string& message);
    static void ThrowRuntimeErrorIf(bool condition, const std::string& message);

    void PushScope();
    void PopScope();

    Scope& CurrentScope();
    const stmt::FunctionDefineNode& GetFunction(const std::string& function_name) const;
    Variable& GetVariable(const std::string& variable_name);

    Int CallFunction(const std::string& function_name, const std::vector<Int>& arguments);

    static bool IsTruthy(Int value) {
        return value != 0;
    }

private:
    std::istream& in_;
    std::ostream& out_;

    std::unordered_map<std::string, const stmt::FunctionDefineNode*> functions_;
    std::vector<Scope> scopes_;

    Int expression_value_ = 0;
    bool is_returning_ = false;
    Int return_value_ = 0;
};

}  // namespace lang::ast::visitors
