#pragma once

#include <unordered_map>
#include <unordered_set>

namespace lang::regex::nfa {

class State {
public:
    friend class StateWrapper;

private:
    std::unordered_map<uint8_t, size_t> edges_;
    std::unordered_set<size_t> eps_edges_;
    size_t final_id_ = -1;
};

}  // namespace lang::regex::nfa
