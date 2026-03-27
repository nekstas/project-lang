#pragma once

#include "../fa/state.h"

namespace lang::regex::dfa {

class State : public fa::State {
    friend class StateWrapper;
};

}  // namespace lang::regex::dfa
