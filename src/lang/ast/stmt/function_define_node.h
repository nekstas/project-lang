#pragma once

#include <cassert>
#include <memory>
#include <optional>
#include <string>
#include <vector>

#include "../node.hpp"
#include "../visitor.h"
#include "block_statement.h"

namespace lang::ast::stmt {

struct FunctionParameter {
    bool is_mutable = false;
    std::string name;
    std::optional<std::string> type_name;
};

class FunctionDefineNode : public Node {
public:
    FunctionDefineNode(std::string function_name, std::vector<FunctionParameter> parameters,
        std::shared_ptr<BlockStatement> body,
        std::optional<std::string> return_type_name = std::nullopt)
        : function_name_(std::move(function_name))
        , parameters_(std::move(parameters))
        , body_(std::move(body))
        , return_type_name_(std::move(return_type_name)) {
        assert(body_);
    }

    void Accept(Visitor& visitor) const override {
        visitor.Visit(*this);
    }

    const std::string& GetFunctionName() const {
        return function_name_;
    }

    const std::vector<FunctionParameter>& GetParameters() const {
        return parameters_;
    }

    const BlockStatement& GetBody() const {
        return *body_;
    }

    const std::optional<std::string>& GetReturnTypeName() const {
        return return_type_name_;
    }

private:
    std::string function_name_;
    std::vector<FunctionParameter> parameters_;
    std::shared_ptr<BlockStatement> body_;
    std::optional<std::string> return_type_name_;
};

}  // namespace lang::ast::stmt
