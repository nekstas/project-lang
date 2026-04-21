#include "module.h"

namespace lib::lang::structure {

std::ostream& operator<<(std::ostream& out, const Module& module) {
    out << "=== Module (" << module.GetFunctionsCount() << " functions) ===\n";
    for (const auto& function : module.GetFunctions()) {
        out << function;
    }
    return out;
}

}  // namespace lib::lang::structure
