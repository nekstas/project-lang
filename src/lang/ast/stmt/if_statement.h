#pragma once

#include <cassert>
#include <memory>

#include "../expression.h"
#include "../statement.h"
#include "../visitor.h"
#include "block_statement.h"

namespace lang::ast::stmt {

class IfStatement : public Statement {
public:
    IfStatement(std::shared_ptr<Expression> condition, std::shared_ptr<BlockStatement> then_block)
        : condition_(std::move(condition)), then_block_(std::move(then_block)) {
        assert(condition_);
        assert(then_block_);
    }

    void Accept(Visitor& visitor) const override {
        visitor.Visit(*this);
    }

    const Expression& GetCondition() const {
        return *condition_;
    }

    const BlockStatement& GetThenBlock() const {
        return *then_block_;
    }

private:
    std::shared_ptr<Expression> condition_;
    std::shared_ptr<BlockStatement> then_block_;
};

}  // namespace lang::ast::stmt
