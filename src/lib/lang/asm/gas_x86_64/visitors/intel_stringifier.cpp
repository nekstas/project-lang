#include "intel_stringifier.h"

#include "../line.h"

namespace lib::lang::asm_::gas_x86_64 {

std::string IntelStringifier::ToString(const Line* line) {
    out_.str("");
    if (line) {
        line->Accept(*this);
    }
    return out_.str();
}

}  // namespace lib::lang::asm_::gas_x86_64
