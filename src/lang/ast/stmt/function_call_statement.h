#pragma once

#include <cassert>
#include <memory>

#include "../statement.h"
#include "../visitor.h"
#include "../expr/function_call_expression.h"

namespace lang::ast::stmt {

class FunctionCallStatement : public Statement {
public:
    explicit FunctionCallStatement(std::shared_ptr<expr::FunctionCallExpression> expression)
        : expression_(std::move(expression)) {
        assert(expression_);
    }

    void Accept(Visitor& visitor) const override {
        visitor.Visit(*this);
    }

    const expr::FunctionCallExpression& GetExpression() const {
        return *expression_;
    }

private:
    std::shared_ptr<expr::FunctionCallExpression> expression_;
};

}  // namespace lang::ast::stmt
