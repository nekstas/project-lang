#include "state_wrapper.h"

#include "../../errors/errors.h"
#include "nfa_wrapper.h"

namespace lib::regex::nfa {

void StateWrapper::AddEpsEdgeTo(StateWrapper another_state) const {
    ASSERT_NOT_NULL(fa_);
    auto& real_state = fa_->ExtractState(*this);
    THROW_IF(real_state.eps_edges_.contains(another_state.state_id_), ::errors::LogicError,
             "Epsilon edge to node with index "
                 << another_state.state_id_ << " already exists at node with index " << state_id_
                 << ".");
    real_state.eps_edges_.insert(another_state.state_id_);
}

StateWrapper StateWrapper::AddEpsEdge() const {
    ASSERT_NOT_NULL(fa_);
    auto another_state = fa_->CreateState();
    AddEpsEdgeTo(another_state);
    return another_state;
}

size_t StateWrapper::MakeFinal() {
    size_t final_id = fa_->NextFinalId();
    SetFinalId(final_id);
    return final_id;
}

}  // namespace lib::regex::nfa
