#pragma once

#include "nfa.h"

namespace lang::regex::nfa {

class StateWrapper {
private:
    friend class NfaWrapper;

public:
    StateWrapper() = default;

private:
    StateWrapper(size_t state_id, NfaWrapper* nfa);

public:
    void AddEdgeTo(StateWrapper another_state, uint8_t code);
    StateWrapper AddEdge(uint8_t code);

    void AddEpsEdgeTo(StateWrapper another_state);
    StateWrapper AddEpsEdge();

    size_t MakeFinal();

private:
    size_t state_id_ = 0;
    NfaWrapper* nfa_ = nullptr;
};

}  // namespace lang::regex::nfa
