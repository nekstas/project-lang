#include "memory.h"

#include "../../../utils/utils.h"
#include "enums/register.h"

namespace lib::lang::asm_::gas_x86_64::mem {

std::ostream& operator<<(std::ostream& out, const StackRbpRelativeAddress& address) {
    return out << "[" << e::Register::RBP << utils::FormatDiff(address.GetDiff()) << "]";
}

}  // namespace lib::lang::asm_::gas_x86_64::mem
