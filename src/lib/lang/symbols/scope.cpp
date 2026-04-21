#include "scope.h"

#include "../../errors/errors.h"

namespace lib::lang::symbols {

Descriptor* Scope::AddDescriptor(std::unique_ptr<Descriptor> descriptor) {
    ASSERT_NOT_NULL(descriptor);
    auto name = descriptor->Name();
    descriptors_[name] = std::move(descriptor);
    return descriptors_.at(name).get();
}

}  // namespace lib::lang::symbols
