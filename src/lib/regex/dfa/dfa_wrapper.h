#pragma once

#include "../fa/fa_wrapper.hpp"
#include "dfa.h"

namespace lib::regex::dfa {

class DfaWrapper : public fa::FaWrapper<DfaWrapper, State, Dfa, StateWrapper> {};

}  // namespace lib::regex::dfa
