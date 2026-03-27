#pragma once

#include <cstdint>

#include "fa.hpp"

namespace lang::regex::fa {

template <typename Derived, typename FaWrapperT>
class StateWrapper {
    template <typename Derived_, typename StateT, typename FaT, typename StateWrapperT>
    friend class FaWrapper;

public:
    StateWrapper() = default;

    StateWrapper(size_t state_id, FaWrapperT* fa) : state_id_(state_id), fa_(fa) {
        THROW_IF(!fa_, ::errors::LogicError, "Pointer to nfa should not be null.");
        THROW_IF(
            !fa_->StateExists(state_id), ::errors::LogicError,
            "state_id " << state_id << "is out of range (size = " << fa_->GetFa().Size() << ").");
    }

public:
    void AddEdgeTo(Derived another_state, uint8_t code) {
        ASSERT_NOT_NULL(fa_);
        auto& real_state = fa_->ExtractState(*static_cast<Derived*>(this));
        THROW_IF(real_state.edges_.contains(code), ::errors::LogicError,
                 "Current NFA implementation support only one edge for char code.");
        real_state.edges_[code] = another_state.state_id_;
    }

    Derived AddEdge(uint8_t code) {
        ASSERT_NOT_NULL(fa_);
        auto another_state = fa_->CreateState();
        AddEdgeTo(another_state, code);
        return another_state;
    }

protected:
    size_t state_id_ = 0;
    FaWrapperT* fa_ = nullptr;
};

}  // namespace lang::regex::fa
