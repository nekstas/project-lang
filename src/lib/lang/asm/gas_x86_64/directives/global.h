#pragma once

#include <string>
#include <vector>

#include "../directive.h"
#include "../visitor.h"

namespace lib::lang::asm_::gas_x86_64::dir {

class Global : public Directive {
public:
    explicit Global(const std::vector<std::string>& names) : names_(names) {}

    explicit Global(const std::string& name) : names_{name} {}

    const std::vector<std::string>& GetNames() const {
        return names_;
    }

    void Accept(Visitor& visitor) const override {
        visitor.Visit(*this);
    }

private:
    std::vector<std::string> names_;
};

}  // namespace lib::lang::asm_::gas_x86_64::dir
