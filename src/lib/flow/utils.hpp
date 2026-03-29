#pragma once

#include <type_traits>
#include <vector>

#include "../utils/magic_templates.hpp"
#include "typed_stage.hpp"

namespace lib::flow::utils {  // StageInT, StageOutT

template <typename Stage>
using StageInT = std::remove_cvref_t<typename ::utils::RunTraits<decltype(&Stage::Run)>::InputType>;

template <typename Stage>
using StageOutT =
    std::remove_cvref_t<typename ::utils::RunTraits<decltype(&Stage::Run)>::OutputType>;

}  // namespace lib::flow::utils

namespace lib::flow::utils {  // StageChainOk

template <typename...>
struct StageChainOk : std::true_type {};

template <typename A, typename B, typename... Rest>
struct StageChainOk<A, B, Rest...> : std::bool_constant<std::is_same_v<StageOutT<A>, StageInT<B>> &&
                                                        StageChainOk<B, Rest...>::value> {};

}  // namespace lib::flow::utils

namespace lib::flow::utils {  // StageChainTypes

template <typename... Stages>
struct StageChainTypes {
    using InputT = StageInT<std::tuple_element_t<0, std::tuple<Stages...>>>;
    using OutputT = StageOutT<std::tuple_element_t<sizeof...(Stages) - 1, std::tuple<Stages...>>>;
    template <typename Derived, typename Context>
    using TypedStageT = TypedStage<Derived, Context, InputT, OutputT>;
};

}  // namespace lib::flow::utils

namespace lib::flow::utils {  // MapPipelineTypes

template <typename Pipeline>
struct MapPipelineTypes {
    using InputT = std::vector<typename Pipeline::InT>;
    using OutputT = std::vector<typename Pipeline::OutT>;
    template <typename Derived, typename Context>
    using TypedStageT = TypedStage<Derived, Context, InputT, OutputT>;
};

}  // namespace lib::flow::utils
