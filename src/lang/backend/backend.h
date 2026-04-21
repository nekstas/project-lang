#pragma once

#include "../../lib/lang/context/base_context.h"
#include "hlir/generator.hpp"

namespace lang::backend {

template <lib::lang::ContextLike Context>
using HlirGenerator = hlir::Generator<Context>;

}  // namespace lang::backend
