#pragma once

#include <cassert>
#include <memory>
#include <vector>

#include "../statement.h"
#include "../visitor.h"

namespace lang::ast::stmt {

class BlockStatement : public Statement {
public:
    explicit BlockStatement(std::vector<std::shared_ptr<Statement>> statements)
        : statements_(std::move(statements)) {
        for (const auto& statement : statements_) {
            assert(statement);
        }
    }

    void Accept(Visitor& visitor) const override {
        visitor.Visit(*this);
    }

    const std::vector<std::shared_ptr<Statement>>& GetStatements() const {
        return statements_;
    }

private:
    std::vector<std::shared_ptr<Statement>> statements_;
};

}  // namespace lang::ast::stmt
