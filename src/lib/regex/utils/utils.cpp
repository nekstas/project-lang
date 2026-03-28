#include "utils.h"

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
        case '\'':
        case '(':
        case '|':
        case ')':
        case '*':
        case '+':
        case '?':
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

}  // namespace lib::regex::utils
