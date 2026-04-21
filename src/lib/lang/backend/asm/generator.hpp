#pragma once

#include "../../../../lib/flow/typed_stage.hpp"
#include "../../asm/unit.hpp"
#include "../../context/base_context.h"
#include "../../structure/module.h"

namespace lib::lang::backend::asm_ {

template <typename AsmLine, ContextLike Context>
class Generator : public flow::TypedStage<Generator<AsmLine, Context>, Context, structure::Module,
                      lang::asm_::Unit<AsmLine>> {
public:
    using UnitType = lang::asm_::Unit<AsmLine>;

public:
    virtual UnitType Run(structure::Module module, Context& ctx) const = 0;
};

}  // namespace lib::lang::backend::asm_
