#pragma once

#include <memory>
#include <optional>
#include <string>

#include "../expression.h"
#include "../statement.h"
#include "../visitor.h"

namespace lang::ast::stmt {

class VariableDeclareStatement : public Statement {
public:
    VariableDeclareStatement(bool is_mutable, std::string variable_name,
        std::optional<std::string> type_name = std::nullopt,
        std::shared_ptr<Expression> initial_value = nullptr)
        : is_mutable_(is_mutable)
        , variable_name_(std::move(variable_name))
        , type_name_(std::move(type_name))
        , initial_value_(std::move(initial_value)) {}

    void Accept(Visitor& visitor) const override {
        visitor.Visit(*this);
    }

    bool IsMutable() const {
        return is_mutable_;
    }

    const std::string& GetVariableName() const {
        return variable_name_;
    }

    const std::optional<std::string>& GetTypeName() const {
        return type_name_;
    }

    bool HasInitialValue() const {
        return initial_value_ != nullptr;
    }

    const Expression& GetInitialValue() const {
        return *initial_value_;
    }

private:
    bool is_mutable_;
    std::string variable_name_;
    std::optional<std::string> type_name_;
    std::shared_ptr<Expression> initial_value_;
};

}  // namespace lang::ast::stmt
