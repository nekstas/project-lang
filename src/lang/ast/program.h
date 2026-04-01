#pragma once

#include <cassert>
#include <memory>
#include <utility>
#include <vector>

#include "node.hpp"
#include "stmt/function_define_node.h"
#include "visitor.h"

namespace lang::ast {

class Program : public Node {
public:
    explicit Program(std::vector<std::shared_ptr<stmt::FunctionDefineNode>> functions)
        : functions_(std::move(functions)) {
        for (const auto& function : functions_) {
            assert(function);
        }
    }

    void Accept(Visitor& visitor) const override {
        visitor.Visit(*this);
    }

    const std::vector<std::shared_ptr<stmt::FunctionDefineNode>>& GetFunctions() const {
        return functions_;
    }

private:
    std::vector<std::shared_ptr<stmt::FunctionDefineNode>> functions_;
};

}  // namespace lang::ast
