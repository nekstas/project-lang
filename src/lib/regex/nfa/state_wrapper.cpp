#include "state_wrapper.h"

#include "../../errors/errors.h"
#include "nfa_wrapper.h"

namespace lang::regex::nfa {

StateWrapper::StateWrapper(size_t state_id, NfaWrapper* nfa) : state_id_(state_id), nfa_(nfa) {
    THROW_IF(!nfa_, ::errors::LogicError, "Pointer to nfa should not be null.");
}

void StateWrapper::AddEdgeTo(StateWrapper another_state, uint8_t code) {
    ASSERT_NOT_NULL(nfa_);
    auto real_state = nfa_->ExtractState(*this);
    THROW_IF(real_state.edges_.contains(code), ::errors::LogicError,
             "Current NFA implementation support only one edge for char code.");
    real_state.edges_[code] = another_state.state_id_;
}

StateWrapper StateWrapper::AddEdge(uint8_t code) {
    ASSERT_NOT_NULL(nfa_);
    auto another_state = nfa_->CreateState();
    AddEdgeTo(another_state, code);
    return another_state;
}

void StateWrapper::AddEpsEdgeTo(StateWrapper another_state) {
    ASSERT_NOT_NULL(nfa_);
    auto real_state = nfa_->ExtractState(*this);
    THROW_IF(real_state.eps_edges_.contains(another_state.state_id_), ::errors::LogicError,
             "Epsilon edge to node with index "
                 << another_state.state_id_ << " already exists at node with index " << state_id_
                 << ".");
    real_state.eps_edges_.insert(another_state.state_id_);
}

StateWrapper StateWrapper::AddEpsEdge() {
    ASSERT_NOT_NULL(nfa_);
    auto another_state = nfa_->CreateState();
    AddEpsEdgeTo(another_state);
    return another_state;
}

size_t StateWrapper::MakeFinal() {
    ASSERT_NOT_NULL(nfa_);
    auto real_state = nfa_->ExtractState(*this);
    real_state.final_id_ = nfa_->NextFinalId();
    return real_state.final_id_;
}

}  // namespace lang::regex::nfa
