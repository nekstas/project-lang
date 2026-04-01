#pragma once

#include "../../lib/lang/context/base_context.h"
#include "../limits/constraints.h"

namespace lang {

struct LangContext : lib::lang::BaseContext {
    limits::LimitsMap limits;
    limits::CounterMap static_counters;
    limits::CounterMap runtime_counters;
};

}  // namespace lang
