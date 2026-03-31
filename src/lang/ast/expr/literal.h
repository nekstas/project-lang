#pragma once

#include <string>

#include "../expression.h"

namespace lang::ast::expr {

class Literal : public Expression {
public:
    explicit Literal(const std::string& value) : value_(value) {}

    const std::string& GetValue() const {
        return value_;
    }

private:
    std::string value_;
};

}  // namespace lang::ast::expr
