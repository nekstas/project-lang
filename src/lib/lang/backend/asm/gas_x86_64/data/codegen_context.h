#pragma once

#include <concepts>

#include "frame_layout.h"

namespace lib::lang::backend::asm_::gas_x86_64 {

struct CodegenContext : BaseContext {
    // TODO: Возможно сделать здесь обёртки как в BaseContext
    std::unordered_map<structure::Function*, FrameLayout> frames;
};

template <typename T>
concept CodegenContextLike = std::derived_from<T, CodegenContext>;

}  // namespace lib::lang::backend::asm_::gas_x86_64
