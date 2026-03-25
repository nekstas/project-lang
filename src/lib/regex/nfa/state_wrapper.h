#pragma once

#include "data.h"

namespace lang::regex::nfa {

class StateWrapper {
private:
    friend class DataWrapper;

public:
    StateWrapper() = default;

private:
    StateWrapper(size_t state_id, DataWrapper* data);

public:
    void AddEdgeTo(StateWrapper another_state, uint8_t code);
    StateWrapper AddEdge(uint8_t code);

    void AddEpsEdgeTo(StateWrapper another_state);
    StateWrapper AddEpsEdge();

    size_t MakeFinal();

private:
    size_t state_id_ = 0;
    DataWrapper* data_ = nullptr;
};

}  // namespace lang::regex::nfa
