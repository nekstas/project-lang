#include "frame_layout.h"

#include "../../../../../errors/errors.h"
#include "../../../../../utils/utils.h"

namespace lib::lang::backend::asm_::gas_x86_64 {

void FrameLayout::RegisterLocal(symbols::LocalValueDescriptor* desc) {
    // TODO: при появлении нескольких типов разных размеров поменять всё
    stack_size_ = utils::AlignUp(stack_size_ + kInt64Size, kInt64Alignment);
    locals_[desc] = -stack_size_;
    EnsureInvariants();
}

void FrameLayout::End() {
    stack_size_ = utils::AlignUp(stack_size_, kStackFrameAlignment);
    EnsureInvariants();
}

void FrameLayout::EnsureInvariants() const {
    TEMP_ASSERT(stack_size_ <= kMaxStackSize);
}

}  // namespace lib::lang::backend::asm_::gas_x86_64
