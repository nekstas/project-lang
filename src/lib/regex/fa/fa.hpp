#pragma once

#include <vector>

#include "../../errors/errors.h"
#include "../fwd.h"

namespace lib::regex::fa {

template <typename StateT>
class Fa {
    template <typename Derived, typename StateT_, typename FaT, typename StateWrapperT>
    friend class FaWrapper;

public:
    size_t Size() const {
        return states_.size();
    }

    size_t GetFinalStatesNumber() const {
        return final_states_number_;
    }

    const StateT& GetState(size_t state_id) const {
        THROW_IF(state_id >= states_.size(), ::errors::LogicError,
                 "Unknown state_id = " << state_id);
        return states_[state_id];
    }

    static size_t GetRootId() {
        return 0;
    }

protected:
    std::vector<StateT> states_;
    size_t final_states_number_ = 0;
};

}  // namespace lib::regex::fa
