#pragma once

#include "../fa/state_wrapper.hpp"
#include "dfa.h"

namespace lang::regex::dfa {

class StateWrapper : public fa::StateWrapper<StateWrapper, DfaWrapper> {
    friend class DfaWrapper;

public:
    using fa::StateWrapper<StateWrapper, DfaWrapper>::StateWrapper;
};

}  // namespace lang::regex::dfa
