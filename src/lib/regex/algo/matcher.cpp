#include "matcher.h"

namespace lang::regex::algo {

void Matcher::UpdateResult(const size_t length, const size_t final_id, Result& result) {
    if (final_id != -1 && (!result.matched || length >= result.length)) {
        result.matched = true;
        result.length = length;
        result.final_id = final_id;
    }
}
}  // namespace lang::regex::algo
