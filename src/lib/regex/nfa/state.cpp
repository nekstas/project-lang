#include "state.h"

const std::unordered_set<size_t>& lib::regex::nfa::State::GetEpsEdges() const {
    return eps_edges_;
}
