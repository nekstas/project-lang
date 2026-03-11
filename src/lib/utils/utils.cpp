#include "utils.h"

namespace utils {

bool IsIn(uint8_t ch, std::string_view symbols) {
    return symbols.contains(ch);
}

}  // namespace utils
