#pragma once

#include "context.h"
#include "line_span.h"

namespace lib::lang::render {

class LineHighlight {
    friend std::ostream& operator<<(std::ostream& out, const LineHighlight& item);

public:
    LineHighlight(const std::string& line_content, size_t line_number, size_t align_length,
        const LineSpan& line_span);

private:
    std::string line_content_;
    size_t line_number_;
    size_t align_length_;
    LineSpan line_span_;
};

std::ostream& operator<<(std::ostream& out, const LineHighlight& item);

}  // namespace lib::lang::render
