#pragma once
#include "../engines/sources.h"

namespace lib::lang::render {

struct Context {
    const engines::Sources& src;
};

template <typename Context>
static render::Context ConstructRenderContext(const Context& common_ctx) {
    return render::Context{.src = common_ctx.src};
}

}  // namespace lib::lang::render
