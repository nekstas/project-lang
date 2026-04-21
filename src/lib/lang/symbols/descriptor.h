#pragma once

#include <iostream>
#include <string>

namespace lib::lang::symbols {

class Descriptor {
public:
    virtual ~Descriptor() {}

    virtual std::string Name() const = 0;
};

std::ostream& operator<<(std::ostream& out, const Descriptor& descriptor);

}  // namespace lib::lang::symbols
