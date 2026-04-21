#pragma once

#include <ostream>
#include <string>

#include "../../../errors/errors.h"

#define LIST(X)              \
    X(NO_PREFIX, "noprefix") \
    X(PREFIX, "prefix")

namespace lib::lang::asm_::gas_x86_64::e {

enum class IntelSyntax {
#define X(name, str_repr) name,
    LIST(X)
#undef X
};

inline std::string IntelSyntaxToString(IntelSyntax intel_syntax) {
    switch (intel_syntax) {
#define X(name, str_repr)   \
    case IntelSyntax::name: \
        return str_repr;
        LIST(X)
#undef X
        default:
            UNREACHABLE;
    }
}

#undef LIST

inline std::ostream& operator<<(std::ostream& out, IntelSyntax intel_syntax) {
    return out << IntelSyntaxToString(intel_syntax);
}

}  // namespace lib::lang::asm_::gas_x86_64::e
