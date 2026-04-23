#pragma once

#include <ranges>

#include "../../../../structure/module.h"
#include "../data/codegen_context.h"

namespace lib::lang::backend::asm_::gas_x86_64 {

template <CodegenContextLike Context>
class FramesCalculator : public flow::TypedStage<FramesCalculator<Context>, Context,
                             structure::Module, structure::Module> {
public:
    virtual structure::Module Run(structure::Module module, Context& ctx) const {
#ifdef DEBUG_LLIR
        std::cerr << module << "\n";
#endif

        for (auto& function : module.GetFunctions()) {
            auto desc = function->GetDesc();
            auto scope = desc->GetFunctionScope();

            FrameLayout frame_layout;

            // TODO: в будущем при появлении нескольких типов подумать
            // что здесь можно улучшить, а что нужно будет починить
            for (const auto& inner_desc : scope->GetDescriptors() | std::views::values) {
                auto local_desc =
                    symbols::CastDescriptor<symbols::LocalValueDescriptor>(inner_desc.get());
                if (!local_desc) {
                    continue;
                }

                frame_layout.RegisterLocal(local_desc);
            }

            frame_layout.End();
            ctx.frames[desc] = frame_layout;
        }

        return std::move(module);
    }

    std::string Name() const override {
        return "FramesCalculator";
    }
};

}  // namespace lib::lang::backend::asm_::gas_x86_64
