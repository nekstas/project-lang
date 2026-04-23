#pragma once

#include <iostream>

namespace lib::lang::asm_::gas_x86_64::mem {

class StackRbpRelativeAddress {
public:
    explicit StackRbpRelativeAddress(int32_t diff) : diff_(diff) {
    }

    int32_t GetDiff() const {
        return diff_;
    }

private:
    int32_t diff_;
};

std::ostream& operator<<(std::ostream& out, const StackRbpRelativeAddress& address);

}  // namespace lib::lang::asm_::gas_x86_64::mem
