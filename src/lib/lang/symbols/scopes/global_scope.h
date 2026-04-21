#pragma once

#include "../scope.h"

namespace lib::lang::symbols {

class GlobalScope : public Scope {
public:
    FunctionDescriptor* CreateFunction(const std::string& function_name, BaseContext& ctx) {
        auto scope = ctx.symbols.AddScope<FunctionScope>();
        return AddDescriptor<FunctionDescriptor>(function_name, scope);
    }
};

}  // namespace lib::lang::symbols
