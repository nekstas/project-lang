#include "descriptor.h"

namespace lib::lang::symbols {

std::ostream& operator<<(std::ostream& out, const Descriptor& descriptor) {
    return out << "<" << descriptor.Name() << ">";
}

}  // namespace lib::lang::symbols
