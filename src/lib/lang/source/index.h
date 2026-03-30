#pragma once

#include <string>
#include <vector>

#include "line_column.h"
#include "line_column_length.h"
#include "span.h"

namespace lib::lang::source {

class Index {
public:
    explicit Index(const std::string& content);

    size_t Size() const {
        return content_.size();
    }

    size_t GetLinesCount() const {
        return line_starts_.size();
    }

    std::string GetLine(size_t line_number) const;

    LineColumn GetLineColumn(size_t offset) const;
    LineColumnLength GetFirstLineForSpan(const Span& span) const;

private:
    void Init();

    size_t GetLineNumber(size_t offset) const;
    size_t GetLineLength(size_t line_number) const;

    void CalculateLineLength(size_t end);

private:
    const std::string& content_;
    std::vector<size_t> line_starts_;
    std::vector<size_t> line_lengths_;
};

}  // namespace lib::lang::source
