#pragma once

#include "../fa/fa_wrapper.hpp"
#include "dfa.h"

namespace lang::regex::dfa {

class DfaWrapper : public fa::FaWrapper<DfaWrapper, State, Dfa, StateWrapper> {};

}  // namespace lang::regex::dfa
