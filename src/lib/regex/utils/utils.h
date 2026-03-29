#pragma once

#include <cstdint>
#include <optional>
#include <string>

namespace lib::regex::utils {

std::string GetSpecialCharRepr(uint8_t code);
size_t GetUtf8CharLength(uint8_t first_byte);
bool IsAsciiChar(uint8_t code);
std::string EscapeHexByte(uint8_t code);
std::optional<uint8_t> ParseHexByte(const std::string& sequence);

}
