#pragma once

#include "../scope.h"

namespace lib::lang::symbols {

class FunctionScope : public Scope {
public:
    TempVariableDescriptor* CreateTempVar() {
        return AddDescriptor<TempVariableDescriptor>(auto_ids_.NextId(kTempVariablesCounter));
    }

protected:
    static constexpr size_t kTempVariablesCounter = 0;
    utils::AutoIds<1> auto_ids_ = {};
};

}  // namespace lib::lang::symbols
