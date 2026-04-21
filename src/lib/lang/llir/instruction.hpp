#pragma once

#include "../fwd.h"

namespace lib::lang::llir {

class Instruction {
public:
    virtual ~Instruction() {}

    virtual void Accept(Visitor& visitor) const = 0;
};

template <typename T>
const T* CastInstruction(const Instruction* instr) {
    return dynamic_cast<const T*>(instr);
}

template <typename T>
T* CastInstruction(Instruction* instr) {
    return dynamic_cast<T*>(instr);
}

}  // namespace lib::lang::llir
