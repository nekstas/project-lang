#pragma once

#include "../descriptor.h"
#include "../enums.h"

namespace lib::lang::symbols {

class ValueDescriptor : public Descriptor {
public:
    explicit ValueDescriptor(e::Mutable is_mutable) : mutable_(is_mutable) {}

    e::Mutable GetMutable() const {
        return mutable_;
    }

    bool IsMutable() const {
        return mutable_ == e::Mutable::TRUE;
    }

private:
    e::Mutable mutable_;
    // TODO: add type later...
};

}  // namespace lib::lang::symbols
