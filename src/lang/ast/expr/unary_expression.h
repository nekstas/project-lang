#pragma once

#include <cassert>
#include <memory>

#include "../enums/unary_operation.h"
#include "../expression.h"
#include "../visitor.h"

namespace lang::ast::expr {

class UnaryExpression : public Expression {
public:
    UnaryExpression(enums::UnaryOperation operation, std::shared_ptr<Expression> expression)
        : operation_(operation), expression_(std::move(expression)) {
        assert(expression_);
    }

    void Accept(Visitor& visitor) const override {
        visitor.Visit(*this);
    }

    enums::UnaryOperation GetOperation() const {
        return operation_;
    }

    const Expression& GetExpression() const {
        return *expression_;
    }

private:
    enums::UnaryOperation operation_;
    std::shared_ptr<Expression> expression_;
};

}  // namespace lang::ast::expr
