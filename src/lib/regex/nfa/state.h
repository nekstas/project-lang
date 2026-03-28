#pragma once

#include <unordered_set>

#include "../fa/state.h"

namespace lib::regex::nfa {

class State : public fa::State {
    friend class StateWrapper;

public:
    const std::unordered_set<size_t>& GetEpsEdges() const;

protected:
    std::unordered_set<size_t> eps_edges_;
};

}  // namespace lib::regex::nfa
