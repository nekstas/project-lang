#pragma once

#include <sstream>
#include <string>
#include <vector>

namespace lib::flow {

class StopPipeline {
public:
    explicit StopPipeline(const std::string& initial_stage_name) {
        stage_names_.push_back(initial_stage_name);
    }

    void AddStageName(const std::string& stage_name) {
        stage_names_.push_back(stage_name);
    }

    std::string GetLocation() const {
        std::stringstream out;
        for (size_t i = stage_names_.size(); i > 0; --i) {
            out << stage_names_[i - 1];
            if (i != 1) {
                out << " > ";
            }
        }
        return out.str();
    }

private:
    std::vector<std::string> stage_names_;
};

}  // namespace lib::flow
