#pragma once

#include <cstdint>

#include "../../visitor.h"
#include "../literal.h"

namespace lang::hlir::expr::lit {

class IntLiteral : public Literal {
public:
    explicit IntLiteral(int64_t value) : value_(value) {}

    void Accept(Visitor& visitor) const override {
        visitor.Visit(*this);
    }

    int64_t GetValue() const {
        return value_;
    }

private:
    int64_t value_;
};

}  // namespace lang::hlir::expr::lit
