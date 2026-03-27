#include "state_wrapper.h"

#include "../../errors/errors.h"
#include "nfa_wrapper.h"

namespace lang::regex::nfa {

void StateWrapper::AddEpsEdgeTo(StateWrapper another_state) {
    ASSERT_NOT_NULL(fa_);
    auto& real_state = fa_->ExtractState(*this);
    THROW_IF(real_state.eps_edges_.contains(another_state.state_id_), ::errors::LogicError,
             "Epsilon edge to node with index "
                 << another_state.state_id_ << " already exists at node with index " << state_id_
                 << ".");
    real_state.eps_edges_.insert(another_state.state_id_);
}

StateWrapper StateWrapper::AddEpsEdge() {
    ASSERT_NOT_NULL(fa_);
    auto another_state = fa_->CreateState();
    AddEpsEdgeTo(another_state);
    return another_state;
}

size_t StateWrapper::MakeFinal() {
    ASSERT_NOT_NULL(fa_);
    auto& real_state = fa_->ExtractState(*this);
    real_state.final_id_ = fa_->NextFinalId();
    return real_state.final_id_;
}

}  // namespace lang::regex::nfa
