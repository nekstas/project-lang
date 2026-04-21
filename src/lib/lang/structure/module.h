#pragma once

#include <iostream>
#include <memory>
#include <vector>

#include "function.h"

namespace lib::lang::structure {

class Module {
public:
    void AddFunction(Function function) {
        functions_.emplace_back(std::move(function));
    }

    size_t GetFunctionsCount() const {
        return functions_.size();
    }

    const std::vector<Function>& GetFunctions() const {
        return functions_;
    }

private:
    std::vector<Function> functions_;
};

std::ostream& operator<<(std::ostream& out, const Module& module);

}  // namespace lib::lang::structure
