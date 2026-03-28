#pragma once

#include "../fa/fa.hpp"
#include "../fwd.h"
#include "state.h"

namespace lib::regex::dfa {

class Dfa : public fa::Fa<State> {
    friend class DfaWrapper;
};

}  // namespace lib::regex::dfa
