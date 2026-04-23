#pragma once

#include "../../../../asm/gas_x86_64/line.h"
#include "../../../../asm/unit.hpp"
#include "../../../../symbols/descriptors/function_descriptor.h"

namespace lib::lang::backend::asm_::gas_x86_64::impl {

using namespace lang::asm_::gas_x86_64;

using LineType = Line;
using UnitType = lang::asm_::Unit<LineType>;

struct InnerContext {
    UnitType result_;
    const symbols::FunctionDescriptor* current_func_desc_ = nullptr;
};

}
