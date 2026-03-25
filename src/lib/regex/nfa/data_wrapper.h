#pragma once

#include <cstdint>

#include "data.h"

namespace lang::regex::nfa {

class DataWrapper {
public:
    DataWrapper();

    const Data& GetData() const;
    void Clear();

    void InitRoot();
    StateWrapper GetRoot();

    StateWrapper GetState(size_t node_id);
    StateWrapper CreateState();

    size_t NextFinalId();

public:
    State& ExtractState(StateWrapper state);

private:
    Data data_;
};

}  // namespace lang::regex::nfa
