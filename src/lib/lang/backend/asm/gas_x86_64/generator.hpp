#pragma once

#include "../../../../flow/static_pipeline.hpp"
#include "../generator.hpp"
#include "data/codegen_context.h"
#include "stages/codegen.hpp"
#include "stages/frames_calculator.hpp"

namespace lib::lang::backend::asm_::gas_x86_64 {

template <CodegenContextLike Context>
auto MakeGas_x86_64_Generator() {
    return flow::MakeStaticNamedPipeline<Context>(
        "GAS_x86_64_Generator", FramesCalculator<Context>{}, Codegen<Context>{});
}

}  // namespace lib::lang::backend::asm_::gas_x86_64
