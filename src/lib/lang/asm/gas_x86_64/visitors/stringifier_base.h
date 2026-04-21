#pragma once

#include <sstream>
#include <string>

#include "../../unit.hpp"
#include "../visitor.h"

namespace lib::lang::asm_::gas_x86_64 {

class StringifierBase : public Visitor {
public:
    virtual std::string ToString(const Line* line) = 0;

    std::string ToString(const Unit<Line>& unit);

public:
    void Visit(const dir::IntelSyntax& dir) override;

protected:
    std::stringstream out_;
};

}  // namespace lib::lang::asm_::gas_x86_64