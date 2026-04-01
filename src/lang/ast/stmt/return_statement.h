#pragma once

#include <memory>

#include "../expression.h"
#include "../statement.h"
#include "../visitor.h"

namespace lang::ast::stmt {

class ReturnStatement : public Statement {
public:
    explicit ReturnStatement(std::shared_ptr<Expression> expression = nullptr)
        : expression_(std::move(expression)) {}

    void Accept(Visitor& visitor) const override {
        visitor.Visit(*this);
    }

    bool HasExpression() const {
        return expression_ != nullptr;
    }

    const Expression& GetExpression() const {
        return *expression_;
    }

private:
    std::shared_ptr<Expression> expression_;
};

}  // namespace lang::ast::stmt
