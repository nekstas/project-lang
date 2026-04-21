#pragma once

#include "../../../../asm/gas_x86_64/line.h"
#include "../../../../structure/module.h"
#include "../../generator.hpp"
#include "../data/codegen_context.h"

namespace lib::lang::backend::asm_::gas_x86_64 {

template <CodegenContextLike Context>
class Codegen : public Generator<lang::asm_::gas_x86_64::Line, Context> {
private:
    using Super = Generator<lang::asm_::gas_x86_64::Line, Context>;

public:
    Super::UnitType Run(structure::Module module, Context& ctx) const override {
        return {};
    }

    std::string Name() const override {
        return "Codegen";
    }
};

}  // namespace lib::lang::backend::asm_::gas_x86_64
