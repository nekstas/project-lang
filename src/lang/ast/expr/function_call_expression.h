#pragma once

#include <cassert>
#include <memory>
#include <string>
#include <vector>

#include "../expression.h"
#include "../visitor.h"

namespace lang::ast::expr {

class FunctionCallExpression : public Expression {
public:
    FunctionCallExpression(std::string function_name, std::vector<std::shared_ptr<Expression>> arguments)
        : function_name_(std::move(function_name)), arguments_(std::move(arguments)) {
        for (const auto& argument : arguments_) {
            assert(argument);
        }
    }

    void Accept(Visitor& visitor) const override {
        visitor.Visit(*this);
    }

    const std::string& GetFunctionName() const {
        return function_name_;
    }

    const std::vector<std::shared_ptr<Expression>>& GetArguments() const {
        return arguments_;
    }

private:
    std::string function_name_;
    std::vector<std::shared_ptr<Expression>> arguments_;
};

}  // namespace lang::ast::expr
