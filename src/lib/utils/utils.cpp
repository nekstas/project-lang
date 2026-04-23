#include "utils.h"

#include <charconv>
#include <iomanip>
#include <sstream>
#include <string>

#include "../errors/errors.h"
#include "format_stream.h"

namespace utils {

bool IsIn(uint8_t ch, std::string_view symbols) {
    return symbols.contains(ch);
}

size_t NumLength(size_t number) {
    return std::to_string(number).size();
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

size_t GetUtf8Length(const std::string& text, size_t& begin, size_t end) {
    size_t length = 0;
    size_t skip = 0;
    size_t valid_end = begin;
    for (; begin < end; ++begin) {
        size_t char_length = GetUtf8CharLength(text[begin]);
        if (char_length == -1) {
            begin = valid_end;
            return length;
        } else if (char_length == 0) {
            if (skip == 0) {
                begin = valid_end;
                return length;
            } else {
                --skip;
            }
        } else {
            skip = char_length - 1;
        }
        if (skip == 0) {
            ++length;
            valid_end = begin + 1;
        }
    }
    return length;
}

std::string FilterSlashR(const std::string& input) {
    std::stringstream out;
    for (uint8_t code : input) {
        if (code == '\r') {
            continue;
        }
        out << code;
    }
    return out.str();
}

void StripNewline(std::string& text) {
    while (!text.empty() && text.back() == '\n') {
        text.pop_back();
    }
}

void NormalizeEndNewLine(std::string& text) {
    StripNewline(text);
    text.push_back('\n');
}

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
            return FormatStream{} << "\\" << code;
        default:
            UNREACHABLE;
    }
}

std::string EscapeHexByte(uint8_t code) {
    return FormatStream{} << std::hex << std::uppercase << std::setw(2) << std::setfill('0')
                          << static_cast<size_t>(code);
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

std::optional<int64_t> ParseInt64(const std::string& value) {
    int64_t result = 0;
    auto end = value.data() + value.size();
    auto [ptr, ec] = std::from_chars(value.data(), end, result);
    if (ec != std::errc{} || ptr != end) {
        return std::nullopt;
    }
    return result;
}

size_t AlignUp(size_t x, size_t y) {
    return (x + y - 1) / y * y;
}

uint64_t NumToAbs(int64_t num) {
    if (num < 0) {
        return static_cast<uint64_t>(-(num + 1)) + 1;
    }
    return num;
}

std::string FormatDiff(int64_t diff, bool use_spaces) {
    if (diff == 0) {
        return "";
    }

    std::stringstream out;
    if (use_spaces) {
        out << " ";
    }
    if (diff > 0) {
        out << "+";
    } else {
        out << "-";
    }
    if (use_spaces) {
        out << " ";
    }
    out << NumToAbs(diff);

    return out.str();
}

}  // namespace utils
