#include "span.h"

namespace lib::lang::source {

Span::Span(SourceDesc desc, size_t offset, size_t length)
    : desc_(desc), offset_(offset), length_(length) {}

Span Span::FromRange(SourceDesc desc, size_t begin, size_t end) {
    return Span{desc, begin, end - begin};
}

}  // namespace lib::lang::source
