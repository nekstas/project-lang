#pragma once

#include <sstream>
#include <string>

#include "../../../../utils/indentable.h"
#include "../../unit.hpp"
#include "../visitor.h"

namespace lib::lang::asm_::gas_x86_64 {

class StringifierBase : public utils::Indentable, public Visitor {
public:
    explicit StringifierBase(size_t indent_spaces) : Indentable(indent_spaces) {}

    virtual std::string ToString(const gas_x86_64::Line* line) = 0;

    std::string ToString(Unit<gas_x86_64::Line> unit);

public:
    void Visit(const Label& label) override;

    void Visit(const dir::IntelSyntax& dir) override;
    void Visit(const dir::Global& dir) override;
    void Visit(const dir::Section& dir) override;

protected:
    std::stringstream out_;
};

}  // namespace lib::lang::asm_::gas_x86_64