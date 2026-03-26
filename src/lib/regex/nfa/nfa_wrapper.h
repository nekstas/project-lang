#pragma once

#include <cstdint>

#include "nfa.h"

namespace lang::regex::nfa {

class NfaWrapper {
public:
    NfaWrapper();

    const Nfa& GetNfa() const;
    void Clear();

    void InitRoot();
    StateWrapper GetRoot();

    StateWrapper GetState(size_t node_id);
    StateWrapper CreateState();

    size_t NextFinalId();

public:
    State& ExtractState(StateWrapper state);

private:
    Nfa nfa_;
};

}  // namespace lang::regex::nfa
