#pragma once

#include "../fa/fa_wrapper.hpp"
#include "nfa.h"

namespace lang::regex::nfa {

class NfaWrapper : public fa::FaWrapper<NfaWrapper, State, Nfa, StateWrapper> {
public:
    NfaWrapper();

    void Clear();

    void InitRoot();
    size_t NextFinalId();
};

}  // namespace lang::regex::nfa
