#include "index.h"

#include <algorithm>
#include <cassert>

#include "../../utils/utils.h"
#include "../errors/errors.h"

namespace lib::lang::src {

Index::Index(const std::string& content) : content_(content) {
    Init();
}

std::string Index::GetLine(size_t line_number) const {
    size_t begin = line_starts_[line_number - 1];
    size_t end = line_number == line_starts_.size() ? Size() : line_starts_[line_number];
    return content_.substr(begin, end - begin);
}

LineColumn Index::GetLineColumn(size_t offset) const {
    size_t line_number = GetLineNumber(offset);
    size_t line_begin = line_starts_[line_number - 1];
    size_t length = utils::GetUtf8Length(content_, line_begin, offset);
    return {line_number, length + 1};
}

LineColumnLength Index::GetFirstLineForSpan(const Span& span) const {
    auto line_column_begin = GetLineColumn(span.GetBegin());
    auto line_column_end = GetLineColumn(span.GetEnd());

    size_t line_number = line_column_begin.GetLine();
    size_t column = line_column_begin.GetColumn();

    size_t length = -column;
    if (line_number == line_column_end.GetLine()) {
        length += line_column_end.GetColumn();
    } else {
        length += GetLineLength(line_number);
    }

    return {line_number, column, length};
}

void Index::Init() {
    line_starts_.push_back(0);

    for (size_t i = 0; i < Size(); ++i) {
        if (content_[i] == '\n') {
            CalculateLineLength(i + 1);
            line_starts_.push_back(i + 1);
        }
    }

    CalculateLineLength(Size());
}

size_t Index::GetLineNumber(size_t offset) const {
    auto iter = std::upper_bound(line_starts_.begin(), line_starts_.end(), offset);
    size_t index = iter - line_starts_.begin();
    assert(index > 0);
    return index;
}

size_t Index::GetLineLength(size_t line_number) const {
    THROW_IF(line_number >= line_lengths_.size(), ::errors::LogicError,
        "line_number = " << line_number << " is out of range.");
    return line_lengths_[line_number - 1];
}

void Index::CalculateLineLength(size_t end) {
    size_t line_number = line_starts_.size();
    const size_t real_begin = line_starts_.back();
    size_t begin = real_begin;
    size_t length = ::utils::GetUtf8Length(content_, begin, end);
    if (begin < end) {
        auto prefix = content_.substr(real_begin, begin - real_begin);
        errors::InvalidEncodingInfo err_info{prefix, line_number, length};
        THROW(lib::lang::errors::InvalidEncodingError, "", err_info);
    }
    line_lengths_.push_back(length);
}

}  // namespace lib::lang::src
