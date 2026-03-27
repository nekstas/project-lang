#pragma once

#include <cstdint>
#include <unordered_map>

namespace lang::regex::fa {

class State {
    template <typename Derived, typename FaWrapperT>
    friend class StateWrapper;

public:
    size_t GetEdge(uint8_t code) const;
    size_t GetFinalId() const;

protected:
    std::unordered_map<uint8_t, size_t> edges_;
    size_t final_id_ = -1;
};

}  // namespace lang::regex::fa
