#pragma once

#include <cstdint>
#include <optional>
#include <string_view>

namespace utils {

bool IsIn(uint8_t ch, std::string_view symbols);
size_t NumLength(size_t number);
size_t GetUtf8CharLength(uint8_t first_byte);
bool IsAsciiChar(uint8_t code);
size_t GetUtf8Length(const std::string& text, size_t& begin, size_t end);
std::string FilterSlashR(const std::string& input);
void StripNewline(std::string& text);
void NormalizeEndNewLine(std::string& text);
std::string GetSpecialCharRepr(uint8_t code);
std::string EscapeHexByte(uint8_t code);
std::optional<uint8_t> ParseHexByte(const std::string& sequence);

}  // namespace utils
