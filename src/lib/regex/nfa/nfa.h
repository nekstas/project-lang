#pragma once

#include "../fa/fa.hpp"
#include "../fwd.h"
#include "state.h"

namespace lang::regex::nfa {

class Nfa : public fa::Fa<State> {
    friend class NfaWrapper;
};

}  // namespace lang::regex::nfa
