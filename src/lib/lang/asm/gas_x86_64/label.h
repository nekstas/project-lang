#pragma once

#include <string>

#include "line.h"
#include "visitor.h"

namespace lib::lang::asm_::gas_x86_64 {

class Label : public Line {
public:
    explicit Label(const std::string& name) : name_(name) {}

    void Accept(Visitor& visitor) const override {
        visitor.Visit(*this);
    }

    bool NeedIndent() const override {
        return false;
    }

    const std::string& GetName() const {
        return name_;
    }

private:
    std::string name_;
};

}  // namespace lib::lang::asm_::gas_x86_64
