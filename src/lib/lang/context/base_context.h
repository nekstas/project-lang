#pragma once

#include <concepts>

#include "../diag/diag_engine.h"
#include "consts.h"

namespace lib::lang {

struct BaseContext {
    diag::DiagEngine diag{context::consts::kMaxErrors};
};

template <typename T>
concept ContextLike = std::derived_from<T, BaseContext>;

}  // namespace lib::lang
