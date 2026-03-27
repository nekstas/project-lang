#include "nfa.h"

#include "../../errors/errors.h"

namespace lang::regex::nfa {

size_t Nfa::Size() const {
    return states_.size();
}

size_t Nfa::GetFinalStatesNumber() const {
    return final_states_number_;
}

const State& Nfa::GetState(size_t state_id) const {
    THROW_IF(state_id >= states_.size(), ::errors::LogicError, "Unknown state_id = " << state_id);
    return states_[state_id];
}

size_t Nfa::GetRootId() {
    return 0;
}

}  // namespace lang::regex::nfa
