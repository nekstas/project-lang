#pragma once
#include <string>

namespace lib::flow {

class TitledPipeline {
public:
    TitledPipeline() : TitledPipeline("???") {}

    explicit TitledPipeline(const std::string& title) : title_(title) {}

    const std::string& GetTitle() const {
        return title_;
    }

private:
    std::string title_;
};

}  // namespace lib::flow
