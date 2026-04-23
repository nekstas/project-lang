#pragma once

#include <concepts>

#include "../../../../context/base_context.h"
#include "frame_layout.h"

namespace lib::lang::backend::asm_::gas_x86_64 {

struct CodegenContext : BaseContext {
    // TODO: Возможно сделать здесь обёртки как в BaseContext
    std::unordered_map<const symbols::FunctionDescriptor*, FrameLayout> frames;
};

template <typename T>
concept CodegenContextLike = std::derived_from<T, CodegenContext>;

}  // namespace lib::lang::backend::asm_::gas_x86_64
