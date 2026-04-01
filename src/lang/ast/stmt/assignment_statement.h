#pragma once

#include <cassert>
#include <memory>
#include <string>

#include "../expression.h"
#include "../statement.h"
#include "../visitor.h"

namespace lang::ast::stmt {

class AssignmentStatement : public Statement {
public:
    AssignmentStatement(std::string variable_name, std::shared_ptr<Expression> expression)
        : variable_name_(std::move(variable_name)), expression_(std::move(expression)) {
        assert(expression_);
    }

    void Accept(Visitor& visitor) const override {
        visitor.Visit(*this);
    }

    const std::string& GetVariableName() const {
        return variable_name_;
    }

    const Expression& GetExpression() const {
        return *expression_;
    }

private:
    std::string variable_name_;
    std::shared_ptr<Expression> expression_;
};

}  // namespace lang::ast::stmt
