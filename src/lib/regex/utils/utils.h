#pragma once

#include <cstdint>
#include <string>

namespace lang::regex::utils {

std::string GetSpecialCharRepr(uint8_t code);
size_t GetUtf8CharLength(uint8_t first_byte);

}
