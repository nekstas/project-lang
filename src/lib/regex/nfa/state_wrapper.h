#pragma once

#include "../fa/state_wrapper.hpp"
#include "nfa.h"

namespace lib::regex::nfa {

class StateWrapper : public fa::StateWrapper<StateWrapper, NfaWrapper> {
    friend class NfaWrapper;

public:
    using fa::StateWrapper<StateWrapper, NfaWrapper>::StateWrapper;

public:
    void AddEpsEdgeTo(StateWrapper another_state) const;
    StateWrapper AddEpsEdge() const;

    size_t MakeFinal();
};

}  // namespace lib::regex::nfa
