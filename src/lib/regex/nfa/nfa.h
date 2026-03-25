#pragma once

#include "data.h"

namespace lang::regex::nfa {

class Nfa {
public:
    explicit Nfa(const Data& data);

private:
    Data data_;
};

}  // namespace lang::regex::nfa
