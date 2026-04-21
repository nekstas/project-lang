#pragma once

#include "value_descriptor.h"

namespace lib::lang::symbols {

class StackValueDescriptor : public ValueDescriptor {
public:
    using ValueDescriptor::ValueDescriptor;
};

}  // namespace lib::lang::symbols
