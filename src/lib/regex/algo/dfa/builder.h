#pragma once

#include "../../dfa/dfa_wrapper.h"
#include "../../fwd.h"

namespace lib::regex::algo::dfa {

class Builder {
public:
    static regex::dfa::Dfa Build(const regex::nfa::Nfa& nfa);
};

}  // namespace lib::regex::algo::dfa
