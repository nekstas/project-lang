#pragma once

#include "../fa/state_wrapper.hpp"

namespace lib::regex::dfa {

class StateWrapper : public fa::StateWrapper<StateWrapper, DfaWrapper> {
    friend class DfaWrapper;

public:
    using fa::StateWrapper<StateWrapper, DfaWrapper>::StateWrapper;
};

}  // namespace lib::regex::dfa
