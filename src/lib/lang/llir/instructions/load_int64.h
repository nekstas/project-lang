#pragma once

#include <cassert>
#include <cstdint>

#include "../../../errors/errors.h"
#include "../../symbols/descriptors/temp_variable_descriptor.h"
#include "../instruction.hpp"
#include "../visitor.h"

namespace lib::lang::llir::instr {

class LoadInt64 : public Instruction {
public:
    explicit LoadInt64(symbols::TempVariableDescriptor* desc, int64_t value)
        : desc_(desc), value_(value) {
        ASSERT_NOT_NULL(desc_);
    }

    void Accept(Visitor& visitor) const override {
        visitor.Visit(*this);
    }

    const symbols::TempVariableDescriptor& GetDesc() const {
        return *desc_;
    }

    int64_t GetValue() const {
        return value_;
    }

private:
    symbols::TempVariableDescriptor* desc_;
    int64_t value_;
};

}  // namespace lib::lang::llir::instr