#pragma once

#include "../../fwd.h"
#include "../descriptor.h"
#include "../scopes/function_scope.h"

namespace lib::lang::symbols {

class FunctionDescriptor : public Descriptor {
public:
    explicit FunctionDescriptor(const std::string& name, FunctionScope* scope)
        : name_(name), scope_(scope) {}

    std::string Name() const override {
        return name_;
    }

    FunctionScope* GetFunctionScope() {
        return scope_;
    }

    const FunctionScope* GetFunctionScope() const {
        return scope_;
    }

private:
    std::string name_;
    FunctionScope* scope_;
};

}  // namespace lib::lang::symbols
