#pragma once

#include <array>
#include <cstdint>
#include <memory>
#include <string>

#include "../../../lib/flow/typed_stage.hpp"
#include "../../../lib/lang/context/base_context.h"
#include "../../../lib/lang/macros.h"
#include "../../ast/expr/binary_expression.h"
#include "../../ast/expr/function_call_expression.h"
#include "../../ast/expr/lit/int_literal.h"
#include "../../ast/expr/unary_expression.h"
#include "../../ast/expr/variable_expression.h"
#include "../../ast/node.hpp"
#include "../../ast/program.h"
#include "../../ast/stmt/assignment_statement.h"
#include "../../ast/stmt/block_statement.h"
#include "../../ast/stmt/function_call_statement.h"
#include "../../ast/stmt/function_define_node.h"
#include "../../ast/stmt/if_else_statement.h"
#include "../../ast/stmt/if_statement.h"
#include "../../ast/stmt/return_statement.h"
#include "../../ast/stmt/variable_declare_statement.h"
#include "../../ast/stmt/while_statement.h"
#include "../../ast/visitor.h"
#include "../../diag/list/constraints.h"
#include "../../limits/constraints.h"

namespace lang::frontend {

template <lib::lang::ContextLike Context>
class StaticConstraintsStage
    : public lib::flow::TypedStage<StaticConstraintsStage<Context>, Context, std::shared_ptr<ast::Node>,
          std::shared_ptr<ast::Node>> {
private:
    class CounterVisitor : public ast::Visitor {
    public:
        const limits::CounterMap& GetCounters() const {
            return counters_;
        }

    public:
        void Visit(const ast::Program& program) override {
            for (const auto& function : program.GetFunctions()) {
                function->Accept(*this);
            }
        }

        void Visit(const ast::expr::lit::IntLiteral&) override {
            counters_.Increment(limits::kMaxStaticIntLiterals);
        }

        void Visit(const ast::expr::BinaryExpression& expr) override {
            counters_.Increment(limits::kMaxStaticBinaryExpressions);
            expr.GetLeftExpression().Accept(*this);
            expr.GetRightExpression().Accept(*this);
        }

        void Visit(const ast::expr::UnaryExpression& expr) override {
            counters_.Increment(limits::kMaxStaticUnaryExpressions);
            expr.GetExpression().Accept(*this);
        }

        void Visit(const ast::expr::FunctionCallExpression& expr) override {
            counters_.Increment(limits::kMaxStaticFunctionCalls);
            for (const auto& argument : expr.GetArguments()) {
                argument->Accept(*this);
            }
        }

        void Visit(const ast::expr::VariableExpression&) override {}

        void Visit(const ast::stmt::FunctionDefineNode& stmt) override {
            counters_.Increment(limits::kMaxStaticFunctions);
            counters_.Increment(limits::kMaxStaticParameters, static_cast<std::int64_t>(stmt.GetParameters().size()));
            stmt.GetBody().Accept(*this);
        }

        void Visit(const ast::stmt::IfStatement& stmt) override {
            counters_.Increment(limits::kMaxStaticIfStatements);
            stmt.GetCondition().Accept(*this);
            stmt.GetThenBlock().Accept(*this);
        }

        void Visit(const ast::stmt::IfElseStatement& stmt) override {
            counters_.Increment(limits::kMaxStaticIfStatements);
            stmt.GetCondition().Accept(*this);
            stmt.GetThenBlock().Accept(*this);
            stmt.GetElseBlock().Accept(*this);
        }

        void Visit(const ast::stmt::WhileStatement& stmt) override {
            counters_.Increment(limits::kMaxStaticWhileStatements);
            stmt.GetCondition().Accept(*this);
            stmt.GetBody().Accept(*this);
        }

        void Visit(const ast::stmt::BlockStatement& stmt) override {
            counters_.Increment(limits::kMaxStaticBlockStatements);
            for (const auto& statement : stmt.GetStatements()) {
                statement->Accept(*this);
            }
        }

        void Visit(const ast::stmt::VariableDeclareStatement& stmt) override {
            counters_.Increment(limits::kMaxStaticVariableDeclarations);
            if (stmt.HasInitialValue()) {
                stmt.GetInitialValue().Accept(*this);
            }
        }

        void Visit(const ast::stmt::AssignmentStatement& stmt) override {
            counters_.Increment(limits::kMaxStaticAssignments);
            stmt.GetExpression().Accept(*this);
        }

        void Visit(const ast::stmt::ReturnStatement& stmt) override {
            counters_.Increment(limits::kMaxStaticReturnStatements);
            if (stmt.HasExpression()) {
                stmt.GetExpression().Accept(*this);
            }
        }

        void Visit(const ast::stmt::FunctionCallStatement& stmt) override {
            stmt.GetExpression().Accept(*this);
        }

    private:
        limits::CounterMap counters_;
    };

public:
    std::shared_ptr<ast::Node> Run(std::shared_ptr<ast::Node> node, Context& ctx) const {
        DIAG_REPORT_IF(node == nullptr, ctx, lang::diag::ConstraintViolationFatal,
            "Internal error: AST is null during static analysis.");

        CounterVisitor visitor;
        node->Accept(visitor);
        ctx.static_counters = visitor.GetCounters();

        static constexpr std::array<const char*, 12> kStaticLimitKeys{
            limits::kMaxStaticFunctions, limits::kMaxStaticParameters, limits::kMaxStaticIfStatements,
            limits::kMaxStaticWhileStatements, limits::kMaxStaticVariableDeclarations,
            limits::kMaxStaticAssignments, limits::kMaxStaticReturnStatements,
            limits::kMaxStaticFunctionCalls, limits::kMaxStaticBinaryExpressions,
            limits::kMaxStaticUnaryExpressions, limits::kMaxStaticIntLiterals,
            limits::kMaxStaticBlockStatements};

        for (const char* limit_key : kStaticLimitKeys) {
            const std::int64_t actual = ctx.static_counters.GetOrDefault(limit_key, 0);
            std::string error;
            if (!limits::CheckLimit(ctx.limits, limit_key, actual, &error)) {
                DIAG_REPORT(ctx, lang::diag::ConstraintViolationFatal, "Static analysis: " + error);
            }
        }

        return node;
    }

    std::string Name() const override {
        return "StaticConstraints";
    }
};

}  // namespace lang::frontend
