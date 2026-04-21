#pragma once

#include "../../../utils/format_stream.h"
#include "../consts.h"
#include "value_descriptor.h"

namespace lib::lang::symbols {

class TempVariableDescriptor : public ValueDescriptor {
public:
    explicit TempVariableDescriptor(size_t number)
        : ValueDescriptor(e::Mutable::FALSE), number_(number) {}

    size_t GetNumber() const {
        return number_;
    }

    std::string Name() const override {
        return utils::FormatStream{} << kTempVariablePrefix << number_;
    }

private:
    size_t number_;
};

}  // namespace lib::lang::symbols
