#pragma once

#include "stack_value_descriptor.h"

namespace lib::lang::symbols {

class LocalValueDescriptor : public StackValueDescriptor {
public:
    using StackValueDescriptor::StackValueDescriptor;
};

}  // namespace lib::lang::symbols
