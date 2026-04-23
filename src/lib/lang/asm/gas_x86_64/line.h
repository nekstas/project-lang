#pragma once

#include "fwd.h"

namespace lib::lang::asm_::gas_x86_64 {

class Line {
public:
    virtual ~Line() {}

    virtual void Accept(Visitor& visitor) const = 0;

    virtual bool NeedIndent() const = 0;
};

template <typename T>
const T* CastLine(const Line* line) {
    return dynamic_cast<const T*>(line);
}

template <typename T>
T* CastLine(Line* line) {
    return dynamic_cast<T*>(line);
}

}  // namespace lib::lang::asm_::gas_x86_64
