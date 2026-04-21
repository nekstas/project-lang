#pragma once

#include <iostream>
#include <string>

namespace lib::lang::symbols {

class Descriptor {
public:
    virtual ~Descriptor() {}

    virtual std::string Name() const = 0;
};

template <typename T>
const T* CastDescriptor(const Descriptor* desc) {
    return dynamic_cast<const T*>(desc);
}

template <typename T>
T* CastDescriptor(Descriptor* desc) {
    return dynamic_cast<T*>(desc);
}

std::ostream& operator<<(std::ostream& out, const Descriptor& descriptor);

}  // namespace lib::lang::symbols
