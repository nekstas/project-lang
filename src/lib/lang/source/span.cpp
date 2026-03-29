#include "span.h"

namespace lib::lang::source {

Span::Span(size_t offset, size_t length) : offset_(offset), length_(length) {}

}  // namespace lib::lang::source
