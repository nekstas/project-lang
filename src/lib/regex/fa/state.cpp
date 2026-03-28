#include "state.h"

#include <ranges>

namespace lib::regex::fa {

size_t State::GetEdge(uint8_t code) const {
    if (edges_.contains(code)) {
        return edges_.at(code);
    }
    return -1;
}

std::set<uint8_t> State::GetEdgeCodes() const {
    std::set<uint8_t> result;
    for (const auto& code : edges_ | std::views::keys) {
        result.insert(code);
    }
    return result;
}

size_t State::GetFinalId() const {
    return final_id_;
}

}  // namespace lib::regex::fa
