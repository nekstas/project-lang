#include "interpreter.h"

#include <cassert>

#include "../../../lib/errors/errors.h"
#include "../../../lib/utils/format_stream.h"
#include "../enums/binary_operation.h"
#include "../enums/unary_operation.h"
#include "../expr/binary_expression.h"
#include "../expr/function_call_expression.h"
#include "../expr/lit/int_literal.h"
#include "../expr/unary_expression.h"
#include "../expr/variable_expression.h"
#include "../program.h"
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

void Interpreter::Execute(const Node* node) {
    ASSERT_NOT_NULL(node);
    functions_.clear();
    scopes_.clear();
    expression_value_ = 0;
    is_returning_ = false;
    return_value_ = 0;
    node->Accept(*this);
}

void Interpreter::Visit(const Program& program) {
    for (const auto& function : program.GetFunctions()) {
        function->Accept(*this);
    }

    ThrowRuntimeErrorIf(!functions_.contains("main"), "Function \"main\" is not defined.");
    (void)CallFunction("main", {});
}

void Interpreter::Visit(const expr::lit::IntLiteral& expr) {
    expression_value_ = std::stoll(expr.GetValue());
}

void Interpreter::Visit(const expr::BinaryExpression& expr) {
    Int left = Eval(expr.GetLeftExpression());
    Int right = Eval(expr.GetRightExpression());

    using Op = ast::enums::BinaryOperation;
    switch (expr.GetOperation()) {
        case Op::SUM:
            expression_value_ = left + right;
            break;
        case Op::SUB:
            expression_value_ = left - right;
            break;
        case Op::MUL:
            expression_value_ = left * right;
            break;
        case Op::DIV:
            ThrowRuntimeErrorIf(right == 0, "Division by zero.");
            expression_value_ = left / right;
            break;
        case Op::EQ:
            expression_value_ = left == right ? 1 : 0;
            break;
        case Op::NE:
            expression_value_ = left != right ? 1 : 0;
            break;
        case Op::LT:
            expression_value_ = left < right ? 1 : 0;
            break;
        case Op::LE:
            expression_value_ = left <= right ? 1 : 0;
            break;
        case Op::GT:
            expression_value_ = left > right ? 1 : 0;
            break;
        case Op::GE:
            expression_value_ = left >= right ? 1 : 0;
            break;
        default:
            UNREACHABLE;
    }
}

void Interpreter::Visit(const expr::UnaryExpression& expr) {
    Int value = Eval(expr.GetExpression());

    using Op = ast::enums::UnaryOperation;
    switch (expr.GetOperation()) {
        case Op::NEG:
            expression_value_ = -value;
            break;
        default:
            UNREACHABLE;
    }
}

void Interpreter::Visit(const expr::FunctionCallExpression& expr) {
    std::vector<Int> arguments;
    arguments.reserve(expr.GetArguments().size());
    for (const auto& argument : expr.GetArguments()) {
        arguments.push_back(Eval(*argument));
    }

    const std::string& function_name = expr.GetFunctionName();
    if (function_name == "print") {
        ThrowRuntimeErrorIf(
            arguments.size() != 1, "Function \"print\" expects exactly 1 argument.");
        out_ << arguments[0] << "\n";
        expression_value_ = 0;
        return;
    }

    if (function_name == "input") {
        ThrowRuntimeErrorIf(!arguments.empty(), "Function \"input\" expects no arguments.");
        Int value = 0;
        in_ >> value;
        ThrowRuntimeErrorIf(in_.fail(), "Failed to read integer from input.");
        expression_value_ = value;
        return;
    }

    expression_value_ = CallFunction(function_name, arguments);
}

void Interpreter::Visit(const expr::VariableExpression& expr) {
    expression_value_ = GetVariable(expr.GetVariableName()).value;
}

void Interpreter::Visit(const stmt::FunctionDefineNode& stmt) {
    ThrowRuntimeErrorIf(functions_.contains(stmt.GetFunctionName()),
        utils::FormatStream() << "Function \"" << stmt.GetFunctionName() << "\" is already defined.");
    functions_[stmt.GetFunctionName()] = &stmt;
}

void Interpreter::Visit(const stmt::IfStatement& stmt) {
    if (IsTruthy(Eval(stmt.GetCondition()))) {
        stmt.GetThenBlock().Accept(*this);
    }
}

void Interpreter::Visit(const stmt::IfElseStatement& stmt) {
    if (IsTruthy(Eval(stmt.GetCondition()))) {
        stmt.GetThenBlock().Accept(*this);
    } else {
        stmt.GetElseBlock().Accept(*this);
    }
}

void Interpreter::Visit(const stmt::WhileStatement& stmt) {
    while (IsTruthy(Eval(stmt.GetCondition()))) {
        stmt.GetBody().Accept(*this);
        if (is_returning_) {
            break;
        }
    }
}

void Interpreter::Visit(const stmt::BlockStatement& stmt) {
    PushScope();
    for (const auto& statement : stmt.GetStatements()) {
        statement->Accept(*this);
        if (is_returning_) {
            break;
        }
    }
    PopScope();
}

void Interpreter::Visit(const stmt::VariableDeclareStatement& stmt) {
    auto& scope = CurrentScope();
    ThrowRuntimeErrorIf(scope.contains(stmt.GetVariableName()),
        utils::FormatStream() << "Variable \"" << stmt.GetVariableName()
                              << "\" is already declared in this scope.");

    Int value = stmt.HasInitialValue() ? Eval(stmt.GetInitialValue()) : 0;
    scope[stmt.GetVariableName()] = Variable{.value = value, .is_mutable = stmt.IsMutable()};
}

void Interpreter::Visit(const stmt::AssignmentStatement& stmt) {
    auto& variable = GetVariable(stmt.GetVariableName());
    ThrowRuntimeErrorIf(!variable.is_mutable,
        utils::FormatStream()
            << "Can't assign to immutable variable \"" << stmt.GetVariableName() << "\".");
    variable.value = Eval(stmt.GetExpression());
}

void Interpreter::Visit(const stmt::ReturnStatement& stmt) {
    return_value_ = stmt.HasExpression() ? Eval(stmt.GetExpression()) : 0;
    is_returning_ = true;
}

void Interpreter::Visit(const stmt::FunctionCallStatement& stmt) {
    (void)Eval(stmt.GetExpression());
}

Interpreter::Int Interpreter::Eval(const Expression& expression) {
    expression.Accept(*this);
    return expression_value_;
}

void Interpreter::ThrowRuntimeError(const std::string& message) {
    throw InterpreterRuntimeError(message);
}

void Interpreter::ThrowRuntimeErrorIf(bool condition, const std::string& message) {
    if (condition) {
        ThrowRuntimeError(message);
    }
}

void Interpreter::PushScope() {
    scopes_.emplace_back();
}

void Interpreter::PopScope() {
    assert(!scopes_.empty());
    scopes_.pop_back();
}

Interpreter::Scope& Interpreter::CurrentScope() {
    ThrowRuntimeErrorIf(scopes_.empty(), "No active scope.");
    return scopes_.back();
}

const stmt::FunctionDefineNode& Interpreter::GetFunction(const std::string& function_name) const {
    ThrowRuntimeErrorIf(!functions_.contains(function_name),
        utils::FormatStream() << "Unknown function \"" << function_name << "\".");
    return *functions_.at(function_name);
}

Interpreter::Variable& Interpreter::GetVariable(const std::string& variable_name) {
    for (size_t i = scopes_.size(); i > 0; --i) {
        auto& scope = scopes_[i - 1];
        if (scope.contains(variable_name)) {
            return scope.at(variable_name);
        }
    }
    ThrowRuntimeError(utils::FormatStream() << "Unknown variable \"" << variable_name << "\".");
    UNREACHABLE;
}

Interpreter::Int Interpreter::CallFunction(
    const std::string& function_name, const std::vector<Int>& arguments) {
    const auto& function = GetFunction(function_name);
    const auto& parameters = function.GetParameters();

    ThrowRuntimeErrorIf(parameters.size() != arguments.size(),
        utils::FormatStream() << "Function \"" << function_name << "\" expects "
                              << parameters.size() << " arguments, got " << arguments.size()
                              << ".");

    const bool prev_is_returning = is_returning_;
    const Int prev_return_value = return_value_;

    is_returning_ = false;
    return_value_ = 0;

    PushScope();
    for (size_t i = 0; i < parameters.size(); ++i) {
        const auto& parameter = parameters[i];
        CurrentScope()[parameter.name] = Variable{
            .value = arguments[i],
            .is_mutable = parameter.is_mutable,
        };
    }

    function.GetBody().Accept(*this);

    Int result = is_returning_ ? return_value_ : 0;

    PopScope();

    is_returning_ = prev_is_returning;
    return_value_ = prev_return_value;
    return result;
}

}  // namespace lang::ast::visitors
