#include "state.h"

namespace lang::regex::fa {

size_t State::GetEdge(uint8_t code) const {
    if (edges_.contains(code)) {
        return edges_.at(code);
    }
    return -1;
}

size_t State::GetFinalId() const {
    return final_id_;
}

}  // namespace lang::regex::fa
