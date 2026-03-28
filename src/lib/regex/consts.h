#pragma once

#include <cstdint>
#include <limits>

namespace lib::regex::consts {

constexpr size_t kStateEdgesCount = 1u << std::numeric_limits<uint8_t>::digits;

}
