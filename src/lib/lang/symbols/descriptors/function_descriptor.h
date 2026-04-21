#pragma once

#include "../descriptor.h"

namespace lib::lang::symbols {

class FunctionDescriptor : public Descriptor {
public:
    explicit FunctionDescriptor(const std::string& name) : name_(name) {}

    std::string Name() const override {
        return name_;
    }

private:
    std::string name_;
};

}  // namespace lib::lang::symbols
