#include "utils.h"

#include <charconv>
#include <iomanip>

#include "../../errors/errors.h"
#include "../../utils/utils.h"

namespace lib::regex::utils {

std::string GetSpecialCharRepr(uint8_t code) {
    switch (code) {
        case '\\':
            return "\\\\";
        case '\n':
            return "\\n";
        case '\t':
            return "\\t";
        case '\r':
            return "\\r";
        case '\f':
            return "\\f";
        case '\v':
            return "\\v";
        case '\'':
        case '(':
        case '|':
        case ')':
        case '*':
        case '+':
        case '?':
        case '^':
        case '[':
        case ']':
            return ::utils::FormatStream{} << "\\" << code;
        default:
            UNREACHABLE;
    }
}

size_t GetUtf8CharLength(uint8_t first_byte) {
    if ((first_byte & 0b10000000u) == 0) {
        return 1;
    } else if ((first_byte & 0b01000000u) == 0) {
        return 0;
    } else if ((first_byte & 0b00100000u) == 0) {
        return 2;
    } else if ((first_byte & 0b00010000u) == 0) {
        return 3;
    } else if ((first_byte & 0b00001000u) == 0) {
        return 4;
    }
    return -1;
}

bool IsAsciiChar(uint8_t code) {
    return GetUtf8CharLength(code) == 1;
}

std::string EscapeHexByte(uint8_t code) {
    return ::utils::FormatStream{} << std::hex << std::uppercase << std::setw(2)
                                   << std::setfill('0') << static_cast<size_t>(code);
}

std::optional<uint8_t> ParseHexByte(const std::string& sequence) {
    THROW_IF(sequence.size() != 2, ::errors::LogicError,
        "Expected hex sequence with length = 2, got " << sequence.size());
    size_t result = 0;
    auto end = sequence.data() + sequence.size();
    auto [ptr, ec] = std::from_chars(sequence.data(), end, result, 16);
    if (ec != std::errc{} || ptr != end) {
        return std::nullopt;
    }
    return result;
}

}  // namespace lib::regex::utils
