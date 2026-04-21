#pragma once

#include <array>
#include <cstddef>

#include "../errors/errors.h"

namespace utils {

template <size_t K>
class AutoIds {
public:
    size_t NextId(size_t index) {
        THROW_IF(ids_[index] == -1, ::errors::LogicError, "All 18e17+ ids already used o_O.");
        return ids_[index]++;
    }

private:
    std::array<size_t, K> ids_;
};

}  // namespace utils
