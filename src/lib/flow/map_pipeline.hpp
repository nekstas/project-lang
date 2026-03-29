#pragma once

#include <sstream>
#include <vector>

#include "utils.hpp"

namespace lib::flow {

template <typename Context, typename Pipeline>
class MapPipeline
    : utils::MapPipelineTypes<Pipeline>,
      public utils::MapPipelineTypes<Pipeline>::template TypedStageT<MapPipeline<Context, Pipeline>,
          Context> {
private:
    using TypeSuper = utils::MapPipelineTypes<Pipeline>;

public:
    explicit MapPipeline(Pipeline pipeline) : pipeline_(std::move(pipeline)) {}

public:
    typename TypeSuper::OutputT Run(typename TypeSuper::InputT inputs, Context& ctx) const {
        typename TypeSuper::OutputT result;
        for (auto& input : inputs) {
            result.emplace_back(pipeline_.Run(std::move(input), ctx));
        }
        return result;
    }

    std::string Name() const override {
        std::stringstream out;
        out << "Map<" << pipeline_.Name() << ">";
        return out.str();
    }

private:
    Pipeline pipeline_;
};

}  // namespace lib::flow
