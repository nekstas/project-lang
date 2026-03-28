#pragma once

#include "fa.hpp"

namespace lib::regex::fa {

template <typename Derived, typename StateT, typename FaT, typename StateWrapperT>
class FaWrapper {
public:
    const FaT& GetFa() const {
        return fa_;
    }

    void Clear() {
        fa_.states_.clear();
        fa_.final_states_number_ = 0;
    }

    StateWrapperT GetRoot() {
        THROW_IF(fa_.states_.empty(), ::errors::LogicError,
                 "Can't get a NFA's root, because it is empty.");
        return GetState(0);
    }

    bool StateExists(size_t state_id) const {
        return state_id < fa_.Size();
    }

    StateWrapperT GetState(size_t state_id) {
        THROW_IF(!StateExists(state_id), ::errors::LogicError,
                 "state_id " << state_id << "is out of range (size = " << fa_.Size() << ").");
        return {state_id, static_cast<Derived*>(this)};
    }

    StateWrapperT CreateState() {
        size_t node_id = fa_.states_.size();
        fa_.states_.emplace_back();
        return {node_id, static_cast<Derived*>(this)};
    }

    StateT& ExtractState(StateWrapperT state) {
        THROW_IF(state.fa_ != this, ::errors::LogicError,
                 "Trying to extract state from different fa.");
        THROW_IF(state.state_id_ >= fa_.Size(), ::errors::LogicError,
                 "Trying to extract state with index (" << state.state_id_ << ") while there are "
                                                        << fa_.Size() << " states.");
        return fa_.states_[state.state_id_];
    }

    void SetFinalStatesNumber(size_t number) {
        fa_.final_states_number_ = number;
    }

protected:
    FaT fa_;
};

}  // namespace lib::regex::fa
