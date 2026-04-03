#pragma once

#include <string>
#include <typeindex>

#include "../utils/move_only_any.h"

namespace lib::flow {

template <typename Context>
class Stage {
public:
    virtual ~Stage() {}

    virtual ::utils::MoveOnlyAny RunAny(::utils::MoveOnlyAny input, Context& ctx) const = 0;
    virtual std::type_index InputType() const = 0;
    virtual std::type_index OutputType() const = 0;

    virtual std::string Name() const = 0;
};

}  // namespace lib::flow
