#include "stringifier_base.h"

#include "../directives/global.h"
#include "../directives/intel_syntax.h"
#include "../directives/section.h"
#include "../label.h"

namespace lib::lang::asm_::gas_x86_64 {

std::string StringifierBase::ToString(Unit<gas_x86_64::Line> unit) {
    std::stringstream result_;
    unit.InsertLine<dir::IntelSyntax>(0, e::IntelSyntax::NO_PREFIX);
    for (const auto& line : unit.GetLines()) {
        if (line && line->NeedIndent()) {
            utils::WithIndent with_indent{*this};
            Line(result_) << ToString(line.get());
        } else {
            Line(result_) << ToString(line.get());
        }
    }
    return result_.str();
}

void StringifierBase::Visit(const Label& label) {
    out_ << label.GetName() << ":";
}

void StringifierBase::Visit(const dir::IntelSyntax& dir) {
    out_ << ".intel_syntax " << dir.GetIntelSyntax();
}

void StringifierBase::Visit(const dir::Global& dir) {
    out_ << ".global ";
    bool is_first = true;
    for (const auto& name : dir.GetNames()) {
        if (!is_first) {
            out_ << ", ";
        }
        out_ << name;
        is_first = false;
    }
}

void StringifierBase::Visit(const dir::Section& dir) {
    out_ << ".section " << dir.GetSection();
}

}  // namespace lib::lang::asm_::gas_x86_64
