#pragma once

#include "../../../../asm/gas_x86_64/directives/global.h"
#include "../../../../asm/gas_x86_64/directives/section.h"
#include "../../../../asm/gas_x86_64/enums/register.h"
#include "../../../../asm/gas_x86_64/enums/section.h"
#include "../../../../asm/gas_x86_64/instructions/mov.h"
#include "../../../../asm/gas_x86_64/instructions/pop.h"
#include "../../../../asm/gas_x86_64/instructions/push.h"
#include "../../../../asm/gas_x86_64/instructions/ret.h"
#include "../../../../asm/gas_x86_64/instructions/sub.h"
#include "../../../../asm/gas_x86_64/label.h"
#include "../../../../asm/gas_x86_64/line.h"
#include "../../../../structure/module.h"
#include "../../generator.hpp"
#include "../data/codegen_context.h"
#include "../impl/llir_to_asm.h"

namespace lib::lang::backend::asm_::gas_x86_64 {

namespace impl {

using namespace lang::asm_::gas_x86_64;

class Codegen {
public:
    Codegen(structure::Module module, CodegenContext& ctx)
        : module_(std::move(module)), ctx_(ctx), llir_to_asm_(ctx, ic_) {}

    UnitType Generate() {
        ic_.result_.AddLine<dir::Section>(e::Section::TEXT);
        ic_.result_.AddEmptyLine();

        for (const auto& function : module_.GetFunctions()) {
            GenerateFunction(*function);
        }
        return std::move(ic_.result_);
    }

private:
    void GenerateBeginOfFile() {
        ic_.result_.AddLine<dir::Section>(e::Section::TEXT);
        ic_.result_.AddEmptyLine();
    }

    void GenerateFunction(const structure::Function& function) {
        ic_.current_func_desc_ = function.GetDesc();

        GenerateFunctionDecl();
        GenerateFunctionPrologue();
        GenerateFunctionBody(function.GetCfg());
        GenerateFunctionEpilogue();
    }

    void GenerateFunctionDecl() {
        auto name = ic_.current_func_desc_->Name();
        ic_.result_.AddLine<dir::Global>(name);
        ic_.result_.AddLine<Label>(name);
    }

    void GenerateFunctionPrologue() {
        const FrameLayout& frame = ctx_.frames.at(ic_.current_func_desc_);
        const auto stack_size = frame.GetStackSize();

        ic_.result_.AddLine<instr::Push>(e::Register::RBP);
        ic_.result_.AddLine<instr::Mov>(op::Reg(e::Register::RBP), op::Reg(e::Register::RSP));
        if (stack_size > 0) {
            ic_.result_.AddLine<instr::Sub>(op::Reg(e::Register::RSP), op::Imm32(frame.GetStackSize()));
        }
    }

    void GenerateFunctionBody(const cfg::ControlFlowGraph& cfg) {
        auto block = cfg.GetFirstBlock();
        auto instructions = block.GetInstructions();
        for (const auto instruction : instructions) {
            llir_to_asm_.Generate(instruction);
        }
    }

    void GenerateFunctionEpilogue() {
        // TODO: Временно
        ic_.result_.AddLine<instr::Mov>(op::Reg(e::Register::RAX), op::Imm32(0));

        ic_.result_.AddLine<instr::Mov>(op::Reg(e::Register::RSP), op::Reg(e::Register::RBP));
        ic_.result_.AddLine<instr::Pop>(e::Register::RBP);
        ic_.result_.AddLine<instr::Ret>();
    }

private:
    structure::Module module_;
    CodegenContext& ctx_;
    InnerContext ic_;
    LlirToAsm llir_to_asm_;
};

}  // namespace impl

template <CodegenContextLike Context>
class Codegen : public Generator<lang::asm_::gas_x86_64::Line, Context> {
private:
    using Super = Generator<lang::asm_::gas_x86_64::Line, Context>;

public:
    Super::UnitType Run(structure::Module module, Context& ctx) const override {
        impl::Codegen codegen(std::move(module), ctx);
        return codegen.Generate();
    }

    std::string Name() const override {
        return "Codegen";
    }
};

}  // namespace lib::lang::backend::asm_::gas_x86_64
