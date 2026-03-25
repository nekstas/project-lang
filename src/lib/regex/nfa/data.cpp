#include "data.h"

#include "state_wrapper.h"

namespace lang::regex::nfa {

size_t Data::Size() const {
    return states_.size();
}

size_t Data::GetFinalStatesNumber() const {
    return final_states_number_;
}

}  // namespace lang::regex::nfa
