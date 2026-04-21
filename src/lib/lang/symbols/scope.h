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
private:
    using DescriptorsMap = std::unordered_map<std::string, std::unique_ptr<Descriptor>>;

public:
    virtual ~Scope() {}

    template <typename DescriptorType, typename... Args>
    DescriptorType* AddDescriptor(Args&&... args) {
        auto desc = AddDescriptor(std::make_unique<DescriptorType>(std::forward<Args>(args)...));
        return dynamic_cast<DescriptorType*>(desc);
    }

    Descriptor* AddDescriptor(std::unique_ptr<Descriptor> descriptor);

    DescriptorsMap& GetDescriptors() {
        return descriptors_;
    }

    const DescriptorsMap& GetDescriptors() const {
        return descriptors_;
    }

private:
    DescriptorsMap descriptors_;
};

template <typename T>
const T* CastScope(const Scope* scope) {
    return dynamic_cast<const T*>(scope);
}

template <typename T>
T* CastScope(Scope* scope) {
    return dynamic_cast<T*>(scope);
}

}  // namespace lib::lang::symbols
