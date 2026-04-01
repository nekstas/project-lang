#pragma once

#include <cassert>
#include <memory>

#include "../expression.h"
#include "../statement.h"
#include "../visitor.h"
#include "block_statement.h"

namespace lang::ast::stmt {

class IfElseStatement : public Statement {
public:
    IfElseStatement(std::shared_ptr<Expression> condition, std::shared_ptr<BlockStatement> then_block,
        std::shared_ptr<BlockStatement> else_block)
        : condition_(std::move(condition))
        , then_block_(std::move(then_block))
        , else_block_(std::move(else_block)) {
        assert(condition_);
        assert(then_block_);
        assert(else_block_);
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

    const BlockStatement& GetElseBlock() const {
        return *else_block_;
    }

private:
    std::shared_ptr<Expression> condition_;
    std::shared_ptr<BlockStatement> then_block_;
    std::shared_ptr<BlockStatement> else_block_;
};

}  // namespace lang::ast::stmt
