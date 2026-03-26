#include "nfa_wrapper.h"

#include "../../errors/errors.h"
#include "nfa.h"
#include "state_wrapper.h"

namespace lang::regex::nfa {

NfaWrapper::NfaWrapper() {
    InitRoot();
}

const Nfa& NfaWrapper::GetNfa() const {
    return nfa_;
}

void NfaWrapper::Clear() {
    nfa_.states_.clear();
    InitRoot();
}

StateWrapper NfaWrapper::GetState(size_t node_id) {
    THROW_IF(node_id >= nfa_.Size(), ::errors::LogicError,
             "node_id " << node_id << "is out of range (size = " << nfa_.Size() << ").");
    return {node_id, this};
}

StateWrapper NfaWrapper::CreateState() {
    size_t node_id = nfa_.states_.size();
    nfa_.states_.emplace_back();
    return {node_id, this};
}

void NfaWrapper::InitRoot() {
    THROW_IF(!nfa_.states_.empty(), ::errors::LogicError,
             "Can't init a NFA if it already has states.");
    CreateState();
}

StateWrapper NfaWrapper::GetRoot() {
    THROW_IF(nfa_.states_.empty(), ::errors::LogicError,
             "Can't get a NFA's root, because it is empty.");
    return GetState(0);
}

State& NfaWrapper::ExtractState(StateWrapper state) {
    THROW_IF(state.nfa_ != this, ::errors::LogicError,
             "Trying to extract state from different data.");
    THROW_IF(state.state_id_ >= nfa_.Size(), ::errors::LogicError,
             "Trying to extract state with index (" << state.state_id_ << ") while there are "
                                                    << nfa_.Size() << " states.");
    return nfa_.states_[state.state_id_];
}

size_t NfaWrapper::NextFinalId() {
    return nfa_.final_states_number_++;
}

}  // namespace lang::regex::nfa
