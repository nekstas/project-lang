#pragma once

#include <cstdint>
#include <string_view>

namespace utils {

bool IsIn(uint8_t ch, std::string_view symbols);

}  // namespace utils
