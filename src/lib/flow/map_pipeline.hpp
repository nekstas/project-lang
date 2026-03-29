#pragma once

#include <sstream>
#include <vector>

#include "stop_pipeline.hpp"
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
        for (size_t i = 0; i < inputs.size(); ++i) {
            try {
                result.emplace_back(pipeline_.Run(std::move(inputs[i]), ctx));
            } catch (StopPipeline& stop_pipeline) {
                stop_pipeline.AddStageName(::utils::FormatStream{} << "Map[" << i << "]");
                throw;
            }
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
