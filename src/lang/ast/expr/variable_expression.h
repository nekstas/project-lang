#pragma once

#include <string>
#include <utility>

#include "../expression.h"
#include "../visitor.h"

namespace lang::ast::expr {

class VariableExpression : public Expression {
public:
    explicit VariableExpression(std::string variable_name) : variable_name_(std::move(variable_name)) {}

    void Accept(Visitor& visitor) const override {
        visitor.Visit(*this);
    }

    const std::string& GetVariableName() const {
        return variable_name_;
    }

private:
    std::string variable_name_;
};

}  // namespace lang::ast::expr
