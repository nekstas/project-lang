#pragma once

#include <memory>

#include "../../enums/binary_operation.h"
#include "../expression.h"

namespace lang::ast::expr {

class BinaryExpression : public Expression {
public:
    BinaryExpression(e::BinaryOperation operation, std::shared_ptr<Expression> left_expression,
        std::shared_ptr<Expression> right_expression)
        : operation_(operation)
        , left_expression_(std::move(left_expression))
        , right_expression_(std::move(right_expression)) {
        assert(left_expression_);
        assert(right_expression_);
    }

    // void Accept(Visitor& visitor) const override {
    //     visitor.Visit(*this);
    // }

    e::BinaryOperation GetOperation() const {
        return operation_;
    }

    const Expression& GetLeftExpression() const {
        return *left_expression_;
    }

    const Expression& GetRightExpression() const {
        return *right_expression_;
    }

private:
    e::BinaryOperation operation_;
    std::shared_ptr<Expression> left_expression_;
    std::shared_ptr<Expression> right_expression_;
};

}  // namespace lang::ast::expr
