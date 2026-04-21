#pragma once

#include "../../lib/lang/backend/asm/gas_x86_64/generator.hpp"
#include "../../lib/lang/context/base_context.h"
#include "hlir/generator.hpp"
#include "llir/generator.hpp"

namespace lang::backend {

template <lib::lang::ContextLike Context>
using HlirGenerator = hlir::Generator<Context>;

template <lib::lang::ContextLike Context>
using LlirGenerator = llir::Generator<Context>;

template <lib::lang::ContextLike Context, typename... Args>
auto AsmGenerator(Args&&... args) {
    return lib::lang::backend::asm_::gas_x86_64::MakeGas_x86_64_Generator<Context>(
        std::forward<Args>(args)...);
}

}  // namespace lang::backend
