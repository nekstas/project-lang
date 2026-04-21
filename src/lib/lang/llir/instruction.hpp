#pragma once

#include "../fwd.h"

namespace lib::lang::llir {

class Instruction {
public:
    virtual ~Instruction() {}

    virtual void Accept(Visitor& visitor) const = 0;
};

template <typename T>
const T* CastNode(const Instruction* node) {
    return dynamic_cast<const T*>(node);
}

template <typename T>
T* CastNode(Instruction* node) {
    return dynamic_cast<T*>(node);
}

}  // namespace lib::lang::llir
