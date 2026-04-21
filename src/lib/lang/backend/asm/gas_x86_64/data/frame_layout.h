#pragma once
#include <unordered_map>

#include "../../../../symbols/descriptors/local_value_descriptor.h"

namespace lib::lang::backend::asm_::gas_x86_64 {

class FrameLayout {
private:
    static constexpr size_t kInt64Size = 8;
    static constexpr size_t kInt64Alignment = 8;
    static constexpr size_t kStackFrameAlignment = 16;
    static constexpr size_t kMaxStackSize = 1ull << 24;

public:
    size_t GetStackSize() const {
        return stack_size_;
    }

public:
    void RegisterLocal(symbols::LocalValueDescriptor* desc);
    void End();

private:
    void EnsureInvariants() const;

private:
    std::unordered_map<symbols::StackValueDescriptor*, ssize_t> locals_;
    size_t stack_size_ = 0;
};

}  // namespace lib::lang::backend::asm_::gas_x86_64
