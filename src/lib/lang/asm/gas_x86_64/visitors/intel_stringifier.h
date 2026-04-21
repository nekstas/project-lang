#pragma once

#include <string>

#include "stringifier_base.h"

namespace lib::lang::asm_::gas_x86_64 {

class IntelStringifier : public StringifierBase {
public:
    using StringifierBase::ToString;
    std::string ToString(const Line* line) override;
};

}  // namespace lib::lang::asm_::gas_x86_64