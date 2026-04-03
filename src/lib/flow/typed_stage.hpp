#pragma once
#include "../errors/errors.h"
#include "stage.hpp"

namespace lib::flow {

template <typename Derived, typename Context, typename In, typename Out>
class TypedStage : public Stage<Context> {
public:
    using InT = In;
    using OutT = Out;

public:
    utils::MoveOnlyAny RunAny(::utils::MoveOnlyAny input, Context& ctx) const final {
        THROW_IF(input.Type() != InputType(), ::errors::LogicError,
            "Unexpected input type of stage \"" << this->Name() << "\"");
        auto typed_input = input.Take<In>();
        auto typed_output = static_cast<const Derived*>(this)->Run(std::move(typed_input), ctx);
        return utils::MoveOnlyAny(std::move(typed_output));
    }

    std::type_index InputType() const final {
        return typeid(In);
    }

    std::type_index OutputType() const final {
        return typeid(Out);
    }
};

}  // namespace lib::flow
