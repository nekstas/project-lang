#pragma once

#include <concepts>

#include "../consts.h"
#include "../engines/diagnostics.h"
#include "../engines/sources.h"
#include "../engines/symbols.h"

namespace lib::lang {

struct BaseContext {
    engines::Diagnostics diag{consts::kMaxErrors};
    engines::Sources src;
    engines::Symbols symbols;
};

template <typename T>
concept ContextLike = std::derived_from<T, BaseContext>;

}  // namespace lib::lang
