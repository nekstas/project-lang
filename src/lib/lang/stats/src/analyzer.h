#pragma once

#include "../../src/source.h"
#include "stats.h"

namespace lib::lang::stats::src {

class Analyzer {
public:
    const Stats& GetStats() const {
        return stats_;
    }

    void AddSource(const ::lib::lang::src::Source& source) {
        size_t lines_count = source.GetIndex().GetLinesCount();
        ++stats_.files_count;
        stats_.max_lines_count = std::max(stats_.max_lines_count, lines_count);
        stats_.total_lines_count += lines_count;
    }

private:
    Stats stats_;
};

}  // namespace lib::lang::stats::src
