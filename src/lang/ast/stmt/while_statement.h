#pragma once

#include <cassert>
#include <memory>

#include "../expression.h"
#include "../statement.h"
#include "../visitor.h"
#include "block_statement.h"

namespace lang::ast::stmt {

class WhileStatement : public Statement {
public:
    WhileStatement(std::shared_ptr<Expression> condition, std::shared_ptr<BlockStatement> body)
        : condition_(std::move(condition)), body_(std::move(body)) {
        assert(condition_);
        assert(body_);
    }

    void Accept(Visitor& visitor) const override {
        visitor.Visit(*this);
    }

    const Expression& GetCondition() const {
        return *condition_;
    }

    const BlockStatement& GetBody() const {
        return *body_;
    }

private:
    std::shared_ptr<Expression> condition_;
    std::shared_ptr<BlockStatement> body_;
};

}  // namespace lang::ast::stmt
