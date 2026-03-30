#include "line_span.h"

#include "../../errors/errors.h"

namespace lib::lang::render {

LineSpan::LineSpan(size_t first_column, size_t length)
    : first_column_(first_column), length_(length) {
    if (first_column_ == 0) {
        if (length_ > 0) {
            --length_;
            ++first_column_;
        }
    }
}

}  // namespace lib::lang::render
