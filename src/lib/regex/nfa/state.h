#pragma once

#include <unordered_map>
#include <unordered_set>
#include <cstdint>

namespace lang::regex::nfa {

class State {
    friend class StateWrapper;

public:
    const std::unordered_set<size_t>& GetEpsEdges() const;
    size_t GetEdge(uint8_t code) const;

private:
    std::unordered_map<uint8_t, size_t> edges_;
    std::unordered_set<size_t> eps_edges_;
    size_t final_id_ = -1;
};

}  // namespace lang::regex::nfa
