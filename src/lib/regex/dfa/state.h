#pragma once

#include "../fa/state.h"

namespace lib::regex::dfa {

class State : public fa::State {
    friend class StateWrapper;
};

}  // namespace lib::regex::dfa
