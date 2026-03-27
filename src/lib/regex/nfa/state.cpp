#include "state.h"

const std::unordered_set<size_t>& lang::regex::nfa::State::GetEpsEdges() const {
    return eps_edges_;
}

size_t lang::regex::nfa::State::GetEdge(uint8_t code) const {
    if (edges_.contains(code)) {
        return edges_.at(code);
    }
    return -1;
}

size_t lang::regex::nfa::State::GetFinalId() const {
    return final_id_;
}
