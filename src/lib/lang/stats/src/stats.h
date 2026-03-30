#pragma once

#include "../../../utils/utils.h"

namespace lib::lang::stats::src {

struct Stats {
    size_t files_count = 0;
    size_t total_lines_count = 0;
    size_t max_lines_count = 0;

    size_t GetMaxLineNumberLen() const {
        return ::utils::NumLength(max_lines_count);
    }
};

}  // namespace lib::lang::stats::src
