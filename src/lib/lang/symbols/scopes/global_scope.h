#pragma once

#include "../scope.h"

namespace lib::lang::symbols {

class GlobalScope : public Scope {
public:
    FunctionDescriptor* CreateFunction(const std::string& function_name) {
        return AddDescriptor<FunctionDescriptor>(function_name);
    }
};

}  // namespace lib::lang::symbols
