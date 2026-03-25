#pragma once

#include <vector>

#include "../fwd.h"
#include "state.h"

namespace lang::regex::nfa {

class Data {
    friend class DataWrapper;

public:
    size_t Size() const;
    size_t GetFinalStatesNumber() const;

private:
    std::vector<State> states_;
    size_t final_states_number_ = 0;
};

}  // namespace lang::regex::nfa
