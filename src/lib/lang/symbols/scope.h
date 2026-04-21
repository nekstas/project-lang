#pragma once

#include <memory>
#include <string>
#include <unordered_map>

#include "../../utils/auto_ids.hpp"
#include "../fwd.h"
#include "descriptor.h"
#include "descriptors/temp_variable_descriptor.h"

namespace lib::lang::symbols {

class Scope {
public:
    virtual ~Scope() {}

    template <typename DescriptorType, typename... Args>
    DescriptorType* AddDescriptor(Args&&... args) {
        auto desc = AddDescriptor(std::make_unique<DescriptorType>(std::forward<Args>(args)...));
        return dynamic_cast<DescriptorType*>(desc);
    }

    Descriptor* AddDescriptor(std::unique_ptr<Descriptor> descriptor);

    TempVariableDescriptor* CreateTempVar() {
        return AddDescriptor<TempVariableDescriptor>(auto_ids_.NextId(kTempVariablesCounter));
    }

private:
    std::unordered_map<std::string, std::unique_ptr<Descriptor>> descriptors_;

protected:
    static constexpr size_t kTempVariablesCounter = 0;
    utils::AutoIds<1> auto_ids_ = {};
};

}  // namespace lib::lang::symbols
