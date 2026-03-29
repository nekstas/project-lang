#pragma once

#include <sstream>
#include <tuple>

#include "stop_pipeline.hpp"
#include "titled_pipeline.h"
#include "utils.hpp"

namespace lib::flow {

template <typename Context, typename... Stages>
class StaticPipeline : utils::StageChainTypes<Stages...>,
                       public utils::StageChainTypes<Stages...>::template TypedStageT<
                           StaticPipeline<Context, Stages...>, Context>,
                       public TitledPipeline {
    static_assert(sizeof...(Stages) > 0, "Pipeline must have at least one stage.");
    static_assert(
        utils::StageChainOk<Stages...>::value, "Stage output/input types are incompatible.");

private:
    using TypeSuper = utils::StageChainTypes<Stages...>;

public:
    explicit StaticPipeline(Stages... stages) : stages_(std::move(stages)...) {}

    explicit StaticPipeline(const std::string& title, Stages... stages)
        : TitledPipeline(title), stages_(std::move(stages)...) {}

    typename TypeSuper::OutputT Run(typename TypeSuper::InputT input, Context& ctx) const {
        return RunImpl<0>(std::move(input), ctx);
    }

    static constexpr size_t Size() {
        return sizeof...(Stages);
    }

    std::string Name() const override {
        std::stringstream out;
        out << GetTitle() << "(";
        NameImpl<0>(out);
        out << ")";
        return out.str();
    }

private:
    template <size_t I, typename T>
    auto RunImpl(T value, Context& ctx) const {
        if constexpr (I == Size()) {
            return value;
        } else {
            const auto& stage = std::get<I>(stages_);
            auto out = RunStageWithCatch(stage, std::move(value), ctx);
            return RunImpl<I + 1>(std::move(out), ctx);
        }
    }

    template <typename Stage, typename T>
    auto RunStageWithCatch(const Stage& stage, T value, Context& ctx) const {
        try {
            return stage.Run(std::move(value), ctx);
        } catch (StopPipeline& stop_pipeline) {
            stop_pipeline.AddStageName(GetTitle());
            throw;
        }
    }

    template <size_t I>
    void NameImpl(std::ostream& out) const {
        if constexpr (I != Size()) {
            if constexpr (I != 0) {
                out << ", ";
            }
            const auto& stage = std::get<I>(stages_);
            out << stage.Name();
            NameImpl<I + 1>(out);
        }
    }

private:
    std::tuple<Stages...> stages_;
};

template <typename Context, typename... Stages>
auto MakeStaticPipeline(Stages&&... stages) {
    return StaticPipeline<Context, std::decay_t<Stages>...>(std::forward<Stages>(stages)...);
};

template <typename Context, typename... Stages>
auto MakeStaticNamedPipeline(std::string title, Stages&&... stages) {
    return StaticPipeline<Context, std::decay_t<Stages>...>(
        std::move(title), std::forward<Stages>(stages)...);
};

}  // namespace lib::flow
