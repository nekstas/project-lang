#pragma once

#include <cstddef>
#include <cstdint>
#include <vector>

#include "../fwd.h"
#include "state.h"

namespace lang::regex::nfa {

class Nfa {
    friend class NfaWrapper;

public:
    size_t Size() const;
    size_t GetFinalStatesNumber() const;
    const State& GetState(size_t state_id) const;
    static size_t GetRootId();

private:
    std::vector<State> states_;
    size_t final_states_number_ = 0;
};

}  // namespace lang::regex::nfa
