#pragma once

#include <cassert>
#include <memory>
#include <sstream>
#include <vector>

#include "stage.hpp"
#include "typed_stage.hpp"

namespace lib::flow {

template <typename Context, typename In, typename Out>
class DynamicPipeline : public TypedStage<DynamicPipeline<Context, In, Out>, Context, In, Out> {
public:
    void AddStage(std::unique_ptr<Stage<Context>> stage, bool is_last = false) {
        THROW_IF(
            ready_, ::errors::LogicError, "Attempt to modify pipeline after added last stage.");
        if (stages_.empty()) {
            THROW_IF(stage->InputType() != this->InputType(), ::errors::LogicError,
                "Input type of the first stage does not equal input type of pipeline.");
        } else {
            THROW_IF(stages_.back()->OutputType() != stage->InputType(), ::errors::LogicError,
                "Output type of the stage with index "
                    << Size() - 1 << " does not equal input type of stage with index " << Size()
                    << ".");
        }
        if (is_last) {
            THROW_IF(stage->OutputType() != this->OutputType(), ::errors::LogicError,
                "Output type of the last stage does not equal output type of pipeline.");
        }
        stages_.emplace_back(std::move(stage));
        ready_ = is_last;
    }

    Out Run(In input, Context& ctx) const {
        THROW_IF(!ready_, ::errors::LogicError,
            "DynamicPipeline is not ready yet. (There are not marked last stage)");
        std::any current = std::move(input);
        for (const auto& stage : stages_) {
            current = stage->RunAny(current, ctx);
        }
        assert(std::type_index(current.type()) == this->OutputType());
        return std::any_cast<Out>(std::move(current));
    }

    std::string Name() const override {
        std::stringstream out;
        out << "[";
        for (size_t i = 0; i < Size(); ++i) {
            if (i != 0) {
                out << ", ";
            }
            out << stages_[i]->Name();
        }
        out << "]";
        return out.str();
    }

    size_t Size() const {
        return stages_.size();
    }

private:
    std::vector<std::unique_ptr<Stage<Context>>> stages_;
    bool ready_ = false;
};

}  // namespace lib::flow
