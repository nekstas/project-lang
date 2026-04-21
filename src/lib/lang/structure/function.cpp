#include "function.h"

namespace lib::lang::structure {

std::ostream& operator<<(std::ostream& out, const Function& function) {
    out << "Function " << function.GetDesc()->Name() << " (" << function.GetBody().Size() << ")\n";
    return out << function.GetBody();
}

}  // namespace lib::lang::structure
