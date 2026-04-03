#pragma once

#include <cstddef>

#include "../source_desc.h"

namespace lib::lang::src {

class Span {
public:
    Span(SourceDesc desc, size_t offset, size_t length);

    SourceDesc GetDesc() const {
        return desc_;
    }

    size_t GetOffset() const {
        return offset_;
    }

    size_t GetLength() const {
        return length_;
    }

    size_t GetBegin() const {
        return offset_;
    }

    size_t GetEnd() const {
        return offset_ + length_;
    }

public:
    static Span FromRange(SourceDesc desc, size_t begin, size_t end);

protected:
    SourceDesc desc_;
    size_t offset_;
    size_t length_;
};

}  // namespace lib::lang::src
