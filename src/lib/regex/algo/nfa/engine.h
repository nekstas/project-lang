#pragma once

#include <set>
#include <string>
#include <vector>

#include "../../nfa/nfa.h"

namespace lang::regex::algo::nfa {

class Engine {
public:
    explicit Engine(const regex::nfa::Nfa& nfa);

public:
    size_t GetRootId() const;
    const std::set<size_t>& EpsClosure(size_t state_id) const;
    std::set<size_t> EpsClosure(const std::set<size_t>& state_ids) const;
    std::set<size_t> Move(const std::set<size_t>& state_ids, uint8_t code) const;
    size_t GetFinalId(const std::set<size_t>& state_ids) const;

private:
    void Build();
    void BuildForState(size_t state_id);

private:
    regex::nfa::Nfa nfa_;
    std::vector<std::set<size_t>> eps_closures_;
};

}  // namespace lang::regex::algo::nfa
