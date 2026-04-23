#pragma once

#include <ostream>
#include <string>

#include "../../../errors/errors.h"

#define LIST(X)      \
    X(RAX, 8, "rax") \
    X(RBP, 8, "rbp") \
    X(RSP, 8, "rsp")

namespace lib::lang::asm_::gas_x86_64::e {

enum class Register {
#define X(name, size, str_repr) name,
    LIST(X)
#undef X
};

inline std::string RegisterToString(Register reg) {
    switch (reg) {
#define X(name, size, str_repr) \
    case Register::name:        \
        return str_repr;
        LIST(X)
#undef X
        default:
            UNREACHABLE;
    }
}

inline size_t RegisterToSize(Register reg) {
    switch (reg) {
#define X(name, size, str_repr) \
    case Register::name:        \
        return size;
        LIST(X)
#undef X
        default:
            UNREACHABLE;
    }
}

#undef LIST

inline std::ostream& operator<<(std::ostream& out, Register reg) {
    return out << RegisterToString(reg);
}

}  // namespace lib::lang::asm_::gas_x86_64::e
