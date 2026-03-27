#include "state.h"

const std::unordered_set<size_t>& lang::regex::nfa::State::GetEpsEdges() const {
    return eps_edges_;
}
