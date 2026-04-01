#include "program.h"

#include <iomanip>

namespace lib::lang::source {

Program::Program(const std::string& name, const std::string& content) : Source(name, content) {}

std::string Program::GetTitle() const {
    return ::utils::FormatStream{} << "Program " << std::quoted(GetName());
}

}  // namespace lib::lang::source
