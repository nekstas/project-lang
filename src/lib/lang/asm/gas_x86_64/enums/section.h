#pragma once

#include <ostream>
#include <string>

#include "../../../errors/errors.h"

#define LIST(X)           \
    X(TEXT, ".text")      \
    X(DATA, ".data")      \
    X(RO_DATA, ".rodata") \
    X(BSS, ".bss")

namespace lib::lang::asm_::gas_x86_64::e {

enum class Section {
#define X(name, str_repr) name,
    LIST(X)
#undef X
};

inline std::string SectionToString(Section section) {
    switch (section) {
#define X(name, str_repr) \
    case Section::name:   \
        return str_repr;
        LIST(X)
#undef X
        default:
            UNREACHABLE;
    }
}

#undef LIST

inline std::ostream& operator<<(std::ostream& out, Section section) {
    return out << SectionToString(section);
}

}  // namespace lib::lang::asm_::gas_x86_64::e
