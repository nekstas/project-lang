#include "nfa_wrapper.h"

#include "../../errors/errors.h"
#include "nfa.h"
#include "state_wrapper.h"

namespace lib::regex::nfa {

NfaWrapper::NfaWrapper() {
    InitRoot();
}

void NfaWrapper::Clear() {
    FaWrapper::Clear();
    InitRoot();
}

void NfaWrapper::InitRoot() {
    THROW_IF(!fa_.states_.empty(), ::errors::LogicError,
             "Can't init a NFA if it already has states.");
    CreateState();
}

size_t NfaWrapper::NextFinalId() {
    return fa_.final_states_number_++;
}

}  // namespace lib::regex::nfa
